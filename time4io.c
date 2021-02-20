#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

// Returns int where 4 lsb are the swithches states
int getsw () {
    return (PORTD >> 8) & 0xf;
}

int getbtns () {
    return ((PORTD >> 4) & 0xe) | ((PORTF >> 1) & 0x1);
}