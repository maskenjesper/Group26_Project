#pragma once

/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];

/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];

/* Declare screen buffer for display output */
extern uint8_t screenbuffer[4][128];

extern uint8_t gameplan[8][126];

// not in use yet: extern Cell cellMap[8][126];