#pragma once

#include "data.h"
#include "func.h"
#include "obj.h"

void enable_interrupt();

#define SCREEN_PIXEL_WIDTH 128
#define SCREEN_PIXEL_HEIGHT 32

#define GAMEPLAN_X1 0
#define GAMEPLAN_Y1 0
#define GAMEPLAN_X2 90
#define GAMEPLAN_Y2 30

void *stdin, *stdout, *stderr;


void gameplay ();
void interrupts_gameplay ();
void interrupts_mainMenu ();
void mainMenu ();
void interrupts_highScore ();
void highScore ();
void gameEnd ();
void interrupts_gameEnd ();

typedef enum {GAMEPLAY, MAINMENU, HIGHSCORE, GAMEEND} GameState;