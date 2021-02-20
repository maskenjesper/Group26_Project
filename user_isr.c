#include <pic32mx.h>

void user_isr () {
    if ((IFS(0) >> 7) & 0x1 == 1) {
        volatile int* LEDs = (volatile int*) 0xbf886110;
        *LEDs = (*LEDs & ~0xff) | ((*LEDs + 1 & 0xff));
    }
    IFS(0) &= ~0x100;
    IFS(0) &= ~0x80;
}