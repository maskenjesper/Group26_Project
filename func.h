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

/* Declare display-related functions from mipslabfunc.c */
void quicksleep(int cyc);
uint8_t spi_send_recv(uint8_t data);
void display_init(void);
void display_string(int line, char *s);
void display_image(int x, const uint8_t *data);
void display_update(void);

void init ();

void display_screenbuffer ();
void screenbuffer_addPixel (uint8_t x, uint8_t y);
void screenbuffer_removePixel (uint8_t x, uint8_t y);

void add_cell (uint8_t x, uint8_t y);
void remove_cell (uint8_t x, uint8_t y);