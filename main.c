#include <stdlib.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "lib.h"
#include <string.h>

ScoreInitialsPair highScores[4];
int score = 0;
char initial[] = {'A', 'A'};
int running = 1;
GameState gameState = MAINMENU;
int timeoutcount = 0;
int locked;
CellContainer cc;
Shape currentShape, nextShape;
Cell C1, C2, C3, C4;

int main () {

	init();

	while (running) {
		switch (gameState) {
			case GAMEPLAY:
				gameplay();
				break;
			case MAINMENU:
				mainMenu();
				break;
			case HIGHSCORE:
				highScore();
				break;
			case GAMEEND:
				highScore();
				break;
		}
	}

	return 0;
}

void gameplay () {
	init_cellcontainer(&cc);

	screenbuffer_drawBoundry();

	PR2 = 31250;

	score = 0;

	// Adds some cells at the bottom of the gameplan
	int m;
	for (m = 0; m < 10; m++) {
		C3 = new_cell(GAMEPLAN_X2, m, 1, 0);
		cellcontainer_addCell(&cc, &C3);
	}

	// Creates randomized array of shape enums
	#define NUMBER_OF_SHAPES 100
	enum shape Shapes[NUMBER_OF_SHAPES];
	int i;
	for (i = 0; i < NUMBER_OF_SHAPES; i++)
		Shapes[i] = shapeGenerator();

	// Main game-loop
	while (1)
		for (i = 0; i < NUMBER_OF_SHAPES; i++ ) {
			locked = 1;

			currentShape = new_shape(Shapes[i], 0, 4, 1, 0);
			if (cellcontainer_checkShapeOverlapping(&cc, &currentShape)) {
				gameEnd();
				gameState = MAINMENU;
				return;
			}
			cellcontainer_addShape(&cc, &currentShape);

			cellcontainer_removeShape(&cc, &nextShape);
			if (i < NUMBER_OF_SHAPES - 1)
				nextShape = new_shape(Shapes[i + 1], 105, 1, 1, 0);
			else
				nextShape = new_shape(Shapes[0], 105, 1, 1, 0);
			cellcontainer_addShape(&cc, &nextShape);

			while (locked)
				if (gameState != GAMEPLAY)
					return;

			// Speedup game
			if (PR2 > 15000)
				PR2 -= 1000;
		}
}

void highScore () {
	display_string(0, "High Scores");

	int i, m;
	for (i = 1; i < 4; i++) {
		char *score = itoaconv(highScores[i].score);
		
		char entry[15];
		entry[0] = highScores[i].c1;
		entry[1] = highScores[i].c2;
		int pos = 2;
		while (*score) {
			entry[pos++] = *score;
			score++;
		}
		display_string(i, entry);
	}

	display_update();

	while (1)
		if (gameState != HIGHSCORE)
			return;
}

void mainMenu () {
	display_string(0, "   TETRIS");
	display_string(1, "1. Start game");
	display_string(2, "2. High scores");
	display_string(3, "");
	display_update();

	while (1) {
		if (getbtns() >> 3 & 0x1) {
			gameState = GAMEPLAY;
			return;
		}
		if (getbtns() >> 2 & 0x1) {
			gameState = HIGHSCORE;
			return;
		}
	}
}

void gameEnd () {
	gameState = GAMEEND;
	display_string(0, "GAME OVER");
	display_string(1, "Type Initials");
	
	
	while (1) {
		display_string(2, initial);
		display_update();
		if (gameState != GAMEEND) {
			addHighscoreEntry(highScores, score, initial[0], initial[1]);
			return;
		}
	}
}

void user_isr () {

	switch (gameState) {
		case GAMEPLAY:
			interrupts_gameplay();
			break;
		case MAINMENU:
			interrupts_mainMenu();
			break;
		case HIGHSCORE:
			interrupts_highScore();
			break;
		case GAMEEND:
			interrupts_gameEnd();
			break;
	}

	// Clear flags
    IFS(0) &= ~0x100;
    IFS(0) &= ~0x80;
	IFS(0) &= ~0x1000;
}

void interrupts_gameplay () {
	/********** TMR2 Interrupt **********/
	if ((IFS(0) >> 8) & 0x1) {	// Move testshape
		if (cellcontainer_moveShape(&cc, &currentShape, RIGHT)) {
			addScore(&score, cellcontainer_scanForRows(&cc));
			locked = 0;
			return;
		}
		if (getbtns() >> 3 & 0x1) {
			cellcontainer_moveShape(&cc, &currentShape, RIGHT);
			cellcontainer_moveShape(&cc, &currentShape, RIGHT);
		}
		draw_frame(&cc, score);
	}

	/********** TMR3 Interrupt **********/
	if ((IFS(0) >> 12) & 0x1) {
		if (getbtns() & 0x1)
			cellcontainer_moveShape(&cc, &currentShape, UP);
		if (getbtns() >> 1 & 0x1)
			cellcontainer_moveShape(&cc, &currentShape, DOWN);
		if (getbtns() >> 2 & 0x1)
			cellcontainer_rotateShape(&cc, &currentShape);
	}

	/*********** SW1 Interrupt ***********/
	if ((IFS(0) >> 7) & 0x1) {
		gameState = MAINMENU;
	}
}

void interrupts_highScore () {
	/*********** SW1 Interrupt ***********/
	if ((IFS(0) >> 7) & 0x1) {
		gameState = MAINMENU;
	}
}

void interrupts_mainMenu() {

}

void interrupts_gameEnd () {
	/********** TMR3 Interrupt **********/
	if ((IFS(0) >> 12) & 0x1) {
		if (getbtns() & 0x1)
			initial[1]++;
		if (getbtns() >> 1 & 0x1)
			initial[1]--;
		if (getbtns() >> 2 & 0x1)
			initial[0]++;
		if (getbtns() >> 3 & 0x1)
			initial[0]--;
	}
	/*********** SW1 Interrupt ***********/
	if ((IFS(0) >> 7) & 0x1) {
		gameState = GAMEPLAY;
	}
}