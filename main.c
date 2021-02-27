/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdlib.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "lib.h"

int timeoutcount = 0;
int locked;
CellContainer cc;
Shape S1, S2;
Cell C1, C2, C3, C4;

void user_isr () {

	/********** TMR2 Interrupt **********/
	if ((IFS(0) >> 8) & 0x1) {		// Tick
		if (getbtns() & 0x1)
			cellcontainer_moveShape(&cc, &S1, UP);
		if (getbtns() >> 1 & 0x1)
			cellcontainer_moveShape(&cc, &S1, DOWN);
		if (getbtns() >> 2 & 0x1)
			cellcontainer_moveShape(&cc, &S1, RIGHT);
		if (getbtns() >> 3 & 0x1)
			cellcontainer_moveShape(&cc, &S1, LEFT);
		screenbuffer_updateCellcontainer(cc);
		screenbuffer_drawBoundry();
		display_screenbuffer();
	}
	if ((IFS(0) >> 8) & 0x1 && timeoutcount++ == 1) {	// Move testshape
		timeoutcount = 0;
		//cellcontainer_moveShape(&cc, &S1, RIGHT);
	}
	/************************************/

	// Clear flags
    IFS(0) &= ~0x100;
    IFS(0) &= ~0x80;
}

int main () {

	init();
	init_cellcontainer(cc);

	S1 = new_shape(T, 50, 4, 1, 0);
	cellcontainer_addShape(&cc, &S1);

	S2 = new_shape(BOX, 30, 4, 1, 0);
	cellcontainer_addShape(&cc, &S2);
	cellcontainer_moveShape(&cc, &S2, DOWN);


	return 0;
}
