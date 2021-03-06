/* mipslabfunc.c
    This file written 2015 by F Lundevall
    Some parts are original code written by Axel Isaksson

    For copyright and licensing, see file COPYING */

#include <stdlib.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "lib.h"

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

/*
 * itoa
 * 
 * Simple conversion routine
 * Converts binary to decimal numbers
 * Returns pointer to (static) char array
 * 
 * The integer argument is converted to a string
 * of digits representing the integer in decimal format.
 * The integer is considered signed, and a minus-sign
 * precedes the string of digits if the number is
 * negative.
 * 
 * This routine will return a varying number of digits, from
 * one digit (for integers in the range 0 through 9) and up to
 * 10 digits and a leading minus-sign (for the largest negative
 * 32-bit integers).
 * 
 * If the integer has the special value
 * 100000...0 (that's 31 zeros), the number cannot be
 * negated. We check for this, and treat this as a special case.
 * If the integer has any other value, the sign is saved separately.
 * 
 * If the integer is negative, it is then converted to
 * its positive counterpart. We then use the positive
 * absolute value for conversion.
 * 
 * Conversion produces the least-significant digits first,
 * which is the reverse of the order in which we wish to
 * print the digits. We therefore store all digits in a buffer,
 * in ASCII form.
 * 
 * To avoid a separate step for reversing the contents of the buffer,
 * the buffer is initialized with an end-of-string marker at the
 * very end of the buffer. The digits produced by conversion are then
 * stored right-to-left in the buffer: starting with the position
 * immediately before the end-of-string marker and proceeding towards
 * the beginning of the buffer.
 * 
 * For this to work, the buffer size must of course be big enough
 * to hold the decimal representation of the largest possible integer,
 * and the minus sign, and the trailing end-of-string marker.
 * The value 24 for ITOA_BUFSIZ was selected to allow conversion of
 * 64-bit quantities; however, the size of an int on your current compiler
 * may not allow this straight away.
 */
#define ITOA_BUFSIZ ( 24 )
char * itoaconv( int num )
{
  register int i, sign;
  static char itoa_buffer[ ITOA_BUFSIZ ];
  static const char maxneg[] = "-2147483648";
  
  itoa_buffer[ ITOA_BUFSIZ - 1 ] = 0;   /* Insert the end-of-string marker. */
  sign = num;                           /* Save sign. */
  if( num < 0 && num - 1 > 0 )          /* Check for most negative integer */
  {
    for( i = 0; i < sizeof( maxneg ); i += 1 )
    itoa_buffer[ i + 1 ] = maxneg[ i ];
    i = 0;
  }
  else
  {
    if( num < 0 ) num = -num;           /* Make number positive. */
    i = ITOA_BUFSIZ - 2;                /* Location for first ASCII digit. */
    do {
      itoa_buffer[ i ] = num % 10 + '0';/* Insert next digit. */
      num = num / 10;                   /* Remove digit from number. */
      i -= 1;                           /* Move index to next empty position. */
    } while( num > 0 );
    if( sign < 0 )
    {
      itoa_buffer[ i ] = '-';
      i -= 1;
    }
  }
  /* Since the loop always sets the index i to the next empty position,
   * we must add 1 in order to return a pointer to the first occupied position. */
  return( &itoa_buffer[ i + 1 ] );
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

    // Init timer 3
    T3CON |= 0x70;      // 256:1 prescale
    PR3 = 31250;        // 80M / 256 / 10
    TMR3 = 0;
    T3CON |= 0x8000;    // Turn on

	// Init Interrupts (TMR2)
	IEC(0) |= 0x100;    // enables timer 2 interrupts
	IPC(2) |= 0x1f;     // set priority
    // Init Interrupts (TMR3)
    IEC(0) |= 0x1000;   // enables timer 2 interrupts
    IPC(3) |= 0xf;      // set priority
	// Init Interrupts (SW1)
	IEC(0) |= 0x80;     // enables SW1 interrupts
	IPC(0) &= ~0x1f000000;  // sets priority and subpriority to 0
	enable_interrupt(); // globally enables interrupts
}

enum shape shapeGenerator () {
    int n;
    srand(TMR2);
    n = rand() % 7;
    return n;
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

void screenbuffer_clear (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    int i, k;
    for (i = x1; i < x2; i++)
        for (k = y1; k < y2; k++)
            screenbuffer_remove(i, k);
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

void screenbuffer_drawBoundry () {
    int i;
    for (i = GAMEPLAN_Y1; i < GAMEPLAN_Y2; i++) {
        screenbuffer_add(GAMEPLAN_X2, i);
    }
    for (i = 0; i < SCREEN_PIXEL_WIDTH; i++) {
        screenbuffer_add(i, 30);
        screenbuffer_add(i, 31);
    }
    for (i = 92; i < 128; i++)
        screenbuffer_add(i, 14);
}

void screenbuffer_updateCellcontainer (CellContainer cc) {
    int i, k;
    screenbuffer_clear(GAMEPLAN_X1, GAMEPLAN_Y1, GAMEPLAN_X2, GAMEPLAN_Y2);
    screenbuffer_clear(91, 0, 128, 30);
    for (i = 0; i < CELLCONTAINER_LENGTH; i++)
        if (cc.cells[i].a == 1)
            screenbuffer_addCell(cc.cells[i].x, 3 * cc.cells[i].y);
}

void draw_frame (CellContainer *cc) {
    screenbuffer_updateCellcontainer(*cc);
    screenbuffer_drawBoundry();
    display_screenbuffer();
}


/********** input-related functions **********/
int getsw () {
    return (PORTD >> 8) & 0xf;
}

int getbtns () {
    return ((PORTD >> 4) & 0xe) | ((PORTF >> 1) & 0x1);
}

void addScore (int *score, int rows) {
    if (rows == 0) {
        return;
    }
    else if (rows == 1) {
        *score += 10;
    }
    else if (rows == 2) {
        *score += 25;
    }
    else if (rows == 3) {
        *score += 40;
    }
    else if (rows == 4) {
        *score += 55;
    }
    else {
        *score += 100;
    }
}