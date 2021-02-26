#pragma once

/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];

/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];

///////////////////////////////////////////////////// Added code below this line /////////////////////////////////////////////////////

/* Declare screen buffer for display output */
extern uint8_t screenbuffer[4][128];
extern uint16_t idcount;