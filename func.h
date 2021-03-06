#pragma once

#include "obj.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

char * itoaconv( int num );

void init ();
enum shape shapeGenerator ();

/* Declare display-related functions */
void quicksleep(int cyc);
uint8_t spi_send_recv(uint8_t data);
void display_init(void);
void display_string(int line, char *s);
void display_image(int x, const uint8_t *data);
void display_update(void);
void display_printScore(char *s);
void display_screenbuffer ();

/* Declare screenbuffer-related functions */
void screenbuffer_addScore (char *s);
void screenbuffer_clear (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void screenbuffer_add (uint8_t x, uint8_t y);
void screenbuffer_remove (uint8_t x, uint8_t y);
void screenbuffer_addCell (uint8_t x, uint8_t y);
void screenbuffer_removeCell (uint8_t x, uint8_t y);
void screenbuffer_drawBoundry ();
void screenbuffer_updateCellcontainer (CellContainer cc);
void draw_frame (CellContainer *cc, int score);

/* Declare input-related functions */
int getsw ();
int getbtns ();

void addScore (int *score, int rows);

void addHighscoreEntry (ScoreInitialsPair highScore[], int newScore, char initial1, char initial2);