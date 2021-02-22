/* mipslabfunc.c
    This file written 2015 by F Lundevall
    Some parts are original code written by Axel Isaksson

    For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "func.h"  /* Declatations for these labs */
#include "data.h"
#include "obj.h"

/* quicksleep:
    A simple function to create a small delay.
    Very inefficient use of computing resources,
    but very handy in some special cases. */
void quicksleep (int cyc) {
    int i;
    for (i = cyc; i > 0; i--);
}

uint8_t spi_send_recv (uint8_t data) {
    while (!(SPI2STAT & 0x08));
    SPI2BUF = data;
    while (!(SPI2STAT & 1));
    return SPI2BUF;
}

void display_init (void) {
    DISPLAY_CHANGE_TO_COMMAND_MODE;
    quicksleep(10);
    DISPLAY_ACTIVATE_VDD;
    quicksleep(1000000);
    
    spi_send_recv(0xAE);
    DISPLAY_ACTIVATE_RESET;
    quicksleep(10);
    DISPLAY_DO_NOT_RESET;
    quicksleep(10);
    
    spi_send_recv(0x8D);
    spi_send_recv(0x14);
    
    spi_send_recv(0xD9);
    spi_send_recv(0xF1);
    
    DISPLAY_ACTIVATE_VBAT;
    quicksleep(10000000);
    
    spi_send_recv(0xA1);
    spi_send_recv(0xC8);
    
    spi_send_recv(0xDA);
    spi_send_recv(0x20);
    
    spi_send_recv(0xAF);
}

void display_string (int line, char *s) {
    int i;
    if (line < 0 || line >= 4)
        return;
    if (!s)
        return;
    
    for (i = 0; i < 16; i++)
        if (*s) {
            textbuffer[line][i] = *s;
            s++;
        } 
        else
            textbuffer[line][i] = ' ';
}

void display_image (int x, const uint8_t *data) {
    int i, j;
    
    for (i = 0; i < 4; i++) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;

        spi_send_recv(0x22);
        spi_send_recv(i);
        
        spi_send_recv(x & 0xF);
        spi_send_recv(0x10 | ((x >> 4) & 0xF));
        
        DISPLAY_CHANGE_TO_DATA_MODE;
        
        for (j = 0; j < 32; j++)
            spi_send_recv(~data[i*32 + j]);
    }
}

void display_update (void) {
    int i, j, k;
    int c;
    for (i = 0; i < 4; i++) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
        spi_send_recv(0x22);
        spi_send_recv(i);
        
        spi_send_recv(0x0);
        spi_send_recv(0x10);
        
        DISPLAY_CHANGE_TO_DATA_MODE;
        
        for (j = 0; j < 16; j++) {
            c = textbuffer[i][j];
            if (c & 0x80)
                continue;
            
            for (k = 0; k < 8; k++)
                spi_send_recv(font[c*8 + k]);
        }
    }
}

///////////////////////////////////////////////////// Added code below this line /////////////////////////////////////////////////////

void init () {
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

	display_init();

	volatile int* LEDs = (volatile int*) 0xbf886100;
	*LEDs &= ~0xff;

    // Init buttons
	TRISD |= 0xfe0;
	TRISF |= 0x1;

	// Init timer 2
	T2CON |= 0x70;      // 256:1 prescale
	PR2 = 31250;        // 80M / 256 / 10
	TMR2 = 0;
	T2CON |= 0x8000;    // Turn on

	// Init Interrupts (TMR2)
	IEC(0) |= 0x100;    // enables timer 2 interrupts
	IPC(2) |= 0x1f;     // set priority
	// Init Interrupts (SW1)
	IEC(0) |= 0x80;     // enables SW1 interrupts
	IPC(0) &= ~0x1f000000;  // sets priority and subpriority to 0
	enable_interrupt(); // globally enables interrupts
}

void display_screenbuffer () {
    int i, j;

    for (i = 0; i < 4; i++) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;

        spi_send_recv(0x22);
        spi_send_recv(i);
        
        spi_send_recv(0x00);
        spi_send_recv(0x10);
        
        DISPLAY_CHANGE_TO_DATA_MODE;
        
        for (j = 0; j < 128; j++)
            spi_send_recv(screenbuffer[i][j]);
    }
}

void screenbuffer_add (uint8_t x, uint8_t y) {
    uint8_t row = y / 8;
    screenbuffer[row][x] |= 1 << y - row * 8;
}

void screenbuffer_remove (uint8_t x, uint8_t y) {
    uint8_t row = y / 8;
    screenbuffer[row][x] &= ~(1 << y - row * 8);
}

void screenbuffer_addCell (uint8_t x, uint8_t y) {
    int i, k;
    for (i = y; i < y + 3; i++)
        for (k = x; k < x + 3; k++)
            screenbuffer_add(k, i);
    screenbuffer_remove(x + 1, y + 1);
}

void screenbuffer_removeCell (uint8_t x, uint8_t y) {
    int i, k;
    for (i = y; i < y + 3; i++)
        for (k = x; k < x + 3; k++)
            screenbuffer_remove(k, i);
}

void screenbuffer_updateGameplan () {
    int i, k;
    for (i = 0; i < 8; i++)
        for (k = 0; k < 126; k++)
            if (gameplan[i][k]) {
                screenbuffer_addCell(k, 3 * i);
                k += 2;
            }
            else
                screenbuffer_removeCell(k, 3 * i);
}

void screenbuffer_drawBoundry () {
    int i;
    for (i = 0; i < 128; i++)
        screenbuffer_add(i, 24);
    for (i = 0; i < 32; i++) {
        screenbuffer_add(63, i);
        screenbuffer_add(64, i);
    }
}
