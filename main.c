/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "lib.h"

void user_isr () {

    if ((IFS(0) >> 7) & 0x1 == 1) {
        volatile int* LEDs = (volatile int*) 0xbf886110;
        *LEDs = (*LEDs & ~0xff) | ((*LEDs + 1 & 0xff));
    }
    
    IFS(0) &= ~0x100;
    IFS(0) &= ~0x80;
}

int main () {

	init();



	return 0;
}

