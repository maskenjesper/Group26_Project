/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "lib.h"

int main () {
        /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while (OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while (OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
    SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

	init();

	display_init();
	display_update();
	display_image(93, icon);

	screenbuffer_addPixel(9, 0);
	display_screenbuffer();

	while (1) {
		int i, k;
		for (i = 0; i < 32; i++)
			for (k = 0; k < 128; k++)
				screenbuffer_addPixel(k, i);
		display_screenbuffer();

		for (i = 0; i < 32; i++)
			for (k = 0; k < 128; k++)
				screenbuffer_removePixel(k, i);
		display_screenbuffer();
	}

	return 0;
}

void init () {
	volatile int* LEDs = (volatile int*) 0xbf886100;
	*LEDs &= ~0xff;

	TRISD |= 0xfe0;
	TRISF |= 0x1;

	// Init timer 2
	T2CON |= 0x70;  // 256:1 prescale
	PR2 = 31250;    // 80M / 256 / 10
	TMR2 = 0;
	T2CON |= 0x8000;

	// Init Interrupts (TMR2)
	IEC(0) |= 0x100;    // enables timer 2 interrupts
	IPC(2) |= 0x1f;     // set priority
	// Init Interrupts (SW1)
	IEC(0) |= 0x80;     // enables SW1 interrupts
	IPC(0) &= ~0x1f000000;  // sets priority and subpriority to 0
	enable_interrupt(); // globally enables interrupts
}