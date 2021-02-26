/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "lib.h"

int timeoutcount = 0;
Shape *s;

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

	int i, k;
	for (i = 0; i < 128; i++)
		for (k = 0; k < 32; k++)
			screenbuffer_add(i, k);

	CellContainer cc;
	init_cellcontainer(&cc);

	screenbuffer_updateCellcontainer(cc);

	return 0;
}
