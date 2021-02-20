/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "lib.h"

int main () {

	init();

	int i, k;
	for (i = 0; i < 32; i++)
		for (k = 0; k < 128; k++)
			screenbuffer_addPixel(k, i);
	display_screenbuffer();

	for (i = 0; i < 32; i++)
		for (k = 0; k < 128; k++)
			screenbuffer_removePixel(k, i);
	display_screenbuffer();

	add_cell(0, 0);
	add_cell(0, 3);
	add_cell(3, 3);
	add_cell(0, 6);

	display_screenbuffer();

	return 0;
}

