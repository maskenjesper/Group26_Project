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
			cellcontainer_rotateShape(&cc, &S1);
<<<<<<< HEAD
		if (getbtns() >> 3 & 0x1)
			cellcontainer_moveShape(&cc, &S1, RIGHT);
=======
>>>>>>> 48b674fc67b1c3cb2158cf338102d8512a17ac1c
		screenbuffer_updateCellcontainer(cc);
		screenbuffer_drawBoundry();
		display_screenbuffer();
	}
	if ((IFS(0) >> 8) & 0x1 && timeoutcount++ == 0) {	// Move testshape
		timeoutcount = 0;
		if (cellcontainer_moveShape(&cc, &S1, RIGHT))
			locked = 0;
	}
	/************************************/

	// Clear flags
    IFS(0) &= ~0x100;
    IFS(0) &= ~0x80;
}

int main () {

	init();
	init_cellcontainer(cc);

<<<<<<< HEAD
	int m;
	for (m = 0; m < 10; m++) {
		C3 = new_cell(GAMEPLAN_X2, m, 1, 0);
		cellcontainer_addCell(&cc, &C3);
	}
=======
	/*S1 = new_shape(STICK, 6, 2, 1, 0);
	cellcontainer_addShape(&cc, &S1);*/
>>>>>>> 48b674fc67b1c3cb2158cf338102d8512a17ac1c

	enum shape Shapes[100];
	int i;
	for (i = 0; i < 100; i++)
		Shapes[i] = ZLEFT;

<<<<<<< HEAD
	Shapes[0] = BOX;
	Shapes[1] = STICK;
	Shapes[2] = T;
	Shapes[3] = LRIGHT;
	Shapes[4] = LLEFT;
	Shapes[5] = ZRIGHT;
	Shapes[6] = ZLEFT;
=======
	/*Shapes[1] = LRIGHT;
	Shapes[2] = LLEFT;
	Shapes[3] = ZRIGHT;
	Shapes[4] = ZLEFT;
	Shapes[5] = ZLEFT;
	Shapes[6] = ZRIGHT;*/
>>>>>>> 48b674fc67b1c3cb2158cf338102d8512a17ac1c

	while (1)
		for (i = 1; i < 100; i++ ) {
			locked = 1;

			S1 = new_shape(Shapes[i], 0, 4, 1, 0);
			cellcontainer_addShape(&cc, &S1);
			
			while (locked);
		}

	return 0;
}
