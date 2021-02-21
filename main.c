/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "lib.h"

int timeoutcount = 0;
struct Shape S1, S2;

void user_isr () {

	// SW1 Interrupt
    if ((IFS(0) >> 7) & 0x1) {
		gameplan_moveShape(&S1, LEFT);
    }

	// TMR2 Interrupt
	if ((IFS(0) >> 8) & 0x1) {
		screenbuffer_updateGameplan();
		display_screenbuffer();
	}
	if ((IFS(0) >> 8) & 0x1 && timeoutcount++ == 9) {
		timeoutcount = 0;
		gameplan_moveShape(&S1, DOWN);
		gameplan_moveShape(&S2, DOWN);
	}

	// Clear flags
    IFS(0) &= ~0x100;
    IFS(0) &= ~0x80;
}

int main () {

	init();

	/*struct Shape S1 = new_shape(BOX);
	gameplan_addShape(&S1);*/

	S1 = new_shape_la(ZRIGHT, 36, 1, 1, 1);
	S2 = new_shape_la(ZLEFT, 45, 3, 1, 1);
	gameplan_addShape(&S1);
	gameplan_addShape(&S2);
	gameplan_removeShape(&S2);

	

	return 0;
}
