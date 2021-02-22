/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "lib.h"

int timeoutcount = 0;
struct Shape S1;

void user_isr () {

	/********** SW1 Interrupt **********/
    if ((IFS(0) >> 7) & 0x1) {
		gameplan_moveShape(&S1, LEFT);
    }

	/********** TMR2 Interrupt **********/
	if ((IFS(0) >> 8) & 0x1) {		// Draw frame
		screenbuffer_updateGameplan();
		screenbuffer_drawBoundry();
		display_screenbuffer();
	}
	if ((IFS(0) >> 8) & 0x1 && timeoutcount++ == 9) {	// Move testshape
		timeoutcount = 0;
		gameplan_moveShape(&S1, DOWN);
	}

	// Clear flags
    IFS(0) &= ~0x100;
    IFS(0) &= ~0x80;
}

int main () {

	init();

	S1 = new_shape(T);

	

	return 0;
}
