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
CellContainer cc;
Cell cell;
Shape s1;

void user_isr () {

	/********** TMR2 Interrupt **********/
	if ((IFS(0) >> 8) & 0x1) {		// Tick
		display_screenbuffer();
	}
	if ((IFS(0) >> 8) & 0x1 && timeoutcount++ == 1) {	// Move testshape
		timeoutcount = 0;

	}
	/************************************/

	// Clear flags
    IFS(0) &= ~0x100;
    IFS(0) &= ~0x80;
}

int main () {

	init();
	init_cellcontainer(cc);

	cell = new_cell(100, 4, 1, 0, 1);
	cellcontainer_addCell(&cc, &cell);
	//cellcontainer_removeCell(&cc, &cell);

	s1 = new_shape(T, 50, 3, 1, 0, 1);
	cellcontainer_addShape(&cc, & s1);

	screenbuffer_updateCellcontainer(cc);

	return 0;
}
