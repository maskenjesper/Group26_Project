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
Shape S1;

void user_isr () {

	/********** TMR2 Interrupt **********/
	if ((IFS(0) >> 8) & 0x1) {		// Tick
		if (getbtns() & 0x1)
			cellcontainer_moveShape(&cc, &S1, UP);
		if (getbtns() >> 1 & 0x1)
			cellcontainer_moveShape(&cc, &S1, DOWN);
		screenbuffer_updateCellcontainer(cc);
		screenbuffer_drawBoundry();
		display_screenbuffer();
	}
	if ((IFS(0) >> 8) & 0x1 && timeoutcount++ == 1) {	// Move testshape
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

	enum shape Shapes[100];
	int i;
	for (i = 0; i < 100; i++)
		Shapes[i] = LLEFT;

	Shapes[1] = BOX;
	Shapes[2] = STICK;
	Shapes[3] = T;
	Shapes[4] = LRIGHT;
	Shapes[5] = ZLEFT;
	Shapes[6] = ZRIGHT;

	while (1)
		for (i = 0; i < 100; i++ ) {
			locked = 1;

			Shape temp = new_shape(Shapes[i], 0, 3, 1, 0, idcount);
			S1 = temp;
			
			while (locked);
		}

	return 0;
}
