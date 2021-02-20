/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);
void quicksleep(int cyc);

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

///////////////////////////////////////////////////// Added code below this line /////////////////////////////////////////////////////

/* Declare screen buffer for display output */
extern uint8_t screenbuffer[4][128];

void display_screenbuffer ();
void screenbuffer_addPixel (uint8_t x, uint8_t y);
void screenbuffer_removePixel (uint8_t x, uint8_t y);

void enable_interrupt();