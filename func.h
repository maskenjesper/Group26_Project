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

void init ();

/* Declare display-related functions */
void quicksleep(int cyc);
uint8_t spi_send_recv(uint8_t data);
void display_init(void);
void display_string(int line, char *s);
void display_image(int x, const uint8_t *data);
void display_update(void);

/* Declare screenbuffer-related functions */
void display_screenbuffer ();
void screenbuffer_add (uint8_t x, uint8_t y);
void screenbuffer_remove (uint8_t x, uint8_t y);
void screenbuffer_addCell (uint8_t x, uint8_t y);
void screenbuffer_removeCell (uint8_t x, uint8_t y);
void screenbuffer_updateGameplan ();
void screenbuffer_drawBoundry ();

/* Declare gameplan-related functions */
void gameplan_addCell (struct Cell *c);
void gameplan_removeCell (struct Cell *c);
enum dir {RIGHT, LEFT, UP, DOWN};
void gameplan_moveCell (struct Cell *c, enum dir d);
void gameplan_moveCells (Cell *c, enum dir d, int l);
void gameplan_addShape (struct Shape *s);
void gameplan_removeShape (struct Shape *s);
// return 1: move failed, return 0: move success
int gameplan_moveShape (struct Shape *s, enum dir d);
// return 1: collision true, return 0: collision false
int cellCollision (Cell *c, enum dir d);
void gameplan_wipe ();