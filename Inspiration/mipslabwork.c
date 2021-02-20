/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int prime = 1234567;
int mytime = 0x5957;
int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void ) {
  if (timeoutcount++ == 9 && (IFS(0) >> 8) & 0x1 == 1) {
    timeoutcount = 0;
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
  }
  if ((IFS(0) >> 7) & 0x1 == 1) {
    volatile int* LEDs = (volatile int*) 0xbf886110;
    *LEDs = (*LEDs & ~0xff) | ((*LEDs + 1 & 0xff));
  }
  if (getbtns() & 0x1)
    mytime = (mytime & ~0xf) | getsw();

  if (getbtns() >> 1 & 0x1)
    mytime = (mytime & ~0xf0) | getsw() << 4;

  if (getbtns() >> 2 & 0x1)
    mytime = (mytime & ~0xf00) | getsw() << 8;

  if (getbtns() >> 3 & 0x1)
    mytime = (mytime & ~0xf000) | getsw() << 12;
 IFS(0) &= ~0x100;
 IFS(0) &= ~0x80;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  /////////////// Added by me /////////////////
  volatile int* LEDs = (volatile int*) 0xbf886100;
  *LEDs &= ~0xff;

  TRISD |= 0xfe0;
  TRISF |= 0x1;

  // Init timer 2
  T2CON |= 0x70;  // 256:1 prescale
  PR2 = 31250;    // 80M / 256 / 10
  TMR2 = 0;
  T2CON |= 0x8000;

  // Init Interrupts (TMR2)
  IEC(0) |= 0x100;    // enables timer 2 interrupts
  IPC(2) |= 0x1f;     // set priority
  // Init Interrupts (SW1)
  IEC(0) |= 0x80;     // enables SW1 interrupts
  IPC(0) &= ~0x1f000000;  // sets priority and subpriority to 0
  enable_interrupt(); // globally enables interrupts
  /////////////////////////////////////////////
  return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
 prime = nextprime( prime );
 display_string( 0, itoaconv( prime ) );
 display_update();
}

