#include <stdlib.h>
#include <stdint.h>
#include "obj.h"

/**************** CELL  ****************/
/*** CONSTRUCTORS ***/
Cell new_cell () {
    Cell c = {.x = 0, .y = 0, .a = 1, .p = 0};
    return c;
}
Cell new_cell_lc (uint8_t x, uint8_t y) {
    Cell c = {.x = x, .y = y, .a = 1, .p = 0};
    return c;
}
Cell new_cell_la (uint8_t x, uint8_t y, uint8_t a, uint8_t p) {
    Cell c = {.x = x, .y = y, .a = a, .p = p};
    return c;
}

/**************** SHAPE ****************/
/*** CONSTRUCTORS ***/
Shape new_shape (shape s) {
    Shape S = {.s = s, .x = 0, .y = 1, .a = 1, .p = 0};
    if (s == BOX) {
        S.c[0] = new_cell();
        S.c[1] = new_cell_lc(0, 1);
        S.c[2] = new_cell_lc(3, 0);
        S.c[3] = new_cell_lc(3, 1);
    }

    else if (s == STICK) {
        S.c[0] = new_cell();
        S.c[1] = new_cell_lc(0, 1);
        S.c[2] = new_cell_lc(0, 2);
        S.c[3] = new_cell_lc(0, 3);
    }

    else if (s == T) {
        S.c[0] = new_cell();
        S.c[1] = new_cell_lc(0, 1);
        S.c[2] = new_cell_lc(3, 1);
        S.c[3] = new_cell_lc(0, 2);
    }

    else if (s == LRIGHT) {
        S.c[0] = new_cell_lc(0, 1);
        S.c[1] = new_cell_lc(0, 2);
        S.c[2] = new_cell_lc(3, 1);
        S.c[3] = new_cell_lc(6, 1);
    }

    else if (s == LLEFT) {
        S.c[0] = new_cell();
        S.c[1] = new_cell_lc(0, 1);
        S.c[2] = new_cell_lc(3, 1);
        S.c[3] = new_cell_lc(6, 1);
    }

    else if (s == ZRIGHT) {
        S.c[0] = new_cell();
        S.c[1] = new_cell_lc(0, 1);
        S.c[2] = new_cell_lc(3, 1);
        S.c[3] = new_cell_lc(3, 2);
    }

    else {
        S.c[0] = new_cell_lc(3, 0);
        S.c[1] = new_cell_lc(0, 1);
        S.c[2] = new_cell_lc(3, 1);
        S.c[3] = new_cell_lc(0, 2);
    }
    return S;
}
Shape new_shape_lc (shape s, uint8_t x, uint8_t y) {
    Shape S = {.s = s, .x = x, .y = y, .a = 1, .p = 0};
    if (s == BOX) {
        S.c[0] = new_cell_lc(x, y - 1);
        S.c[1] = new_cell_lc(x, y);
        S.c[2] = new_cell_lc(x + 3, y - 1);
        S.c[3] = new_cell_lc(x + 3, y);
    }

    else if (s == STICK) {
        S.c[0] = new_cell_lc(x, y - 1);
        S.c[1] = new_cell_lc(x, y);
        S.c[2] = new_cell_lc(x, y + 1);
        S.c[3] = new_cell_lc(x, y + 2);
    }

    else if (s == T) {
        S.c[0] = new_cell_lc(x, y - 1);
        S.c[1] = new_cell_lc(x, y);
        S.c[2] = new_cell_lc(x + 3, y);
        S.c[3] = new_cell_lc(x, y + 1);
    }

    else if (s == LRIGHT) {
        S.c[0] = new_cell_lc(x, y);
        S.c[1] = new_cell_lc(x, y + 1);
        S.c[2] = new_cell_lc(x + 3, y);
        S.c[3] = new_cell_lc(x + 6, y);
    }

    else if (s == LLEFT) {
        S.c[0] = new_cell_lc(x, y - 1);
        S.c[1] = new_cell_lc(x, y);
        S.c[2] = new_cell_lc(x + 3, y);
        S.c[3] = new_cell_lc(x + 6, y);
    }

    else if (s == ZRIGHT) {
        S.c[0] = new_cell_lc(x, y - 1);
        S.c[1] = new_cell_lc(x, y);
        S.c[2] = new_cell_lc(x + 3, y);
        S.c[3] = new_cell_lc(x + 3, y + 1);
    }

    else {
        S.c[0] = new_cell_lc(x + 3, y - 1);
        S.c[1] = new_cell_lc(x, y);
        S.c[2] = new_cell_lc(x + 3, y);
        S.c[3] = new_cell_lc(x, y + 1);
    }
    return S;
}
Shape new_shape_la (shape s, uint8_t x, uint8_t y, uint8_t a, uint8_t p) {
    Shape S = {.s = s, .x = x, .y = y, .a = a, .p = p};
    if (s == BOX) {
        S.c[0] = new_cell_la(x, y - 1, a, p);
        S.c[1] = new_cell_la(x, y, a, p);
        S.c[2] = new_cell_la(x + 3, y - 1, a, p);
        S.c[3] = new_cell_la(x + 3, y, a, p);
    }

    else if (s == STICK) {
        S.c[0] = new_cell_la(x, y - 1, a, p);
        S.c[1] = new_cell_la(x, y, a, p);
        S.c[2] = new_cell_la(x, y + 1, a, p);
        S.c[3] = new_cell_la(x, y + 2, a, p);
    }

    else if (s == T) {
        S.c[0] = new_cell_la(x, y - 1, a, p);
        S.c[1] = new_cell_la(x, y, a, p);
        S.c[2] = new_cell_la(x + 3, y, a, p);
        S.c[3] = new_cell_la(x, y + 1, a, p);
    }

    else if (s == LRIGHT) {
        S.c[0] = new_cell_la(x, y, a, p);
        S.c[1] = new_cell_la(x, y + 1, a, p);
        S.c[2] = new_cell_la(x + 3, y, a, p);
        S.c[3] = new_cell_la(x + 6, y, a, p);
    }

    else if (s == LLEFT) {
        S.c[0] = new_cell_la(x, y - 1, a, p);
        S.c[1] = new_cell_la(x, y, a, p);
        S.c[2] = new_cell_la(x + 3, y, a, p);
        S.c[3] = new_cell_la(x + 6, y, a, p);
    }

    else if (s == ZRIGHT) {
        S.c[0] = new_cell_la(x, y - 1, a, p);
        S.c[1] = new_cell_la(x, y, a, p);
        S.c[2] = new_cell_la(x + 3, y, a, p);
        S.c[3] = new_cell_la(x + 3, y + 1, a, p);
    }

    else {
        S.c[0] = new_cell_la(x + 3, y - 1, a, p);
        S.c[1] = new_cell_la(x, y, a, p);
        S.c[2] = new_cell_la(x + 3, y, a, p);
        S.c[3] = new_cell_la(x, y + 1, a, p);
    }
    return S;
}

/**************** Gameplan ****************/
/*** CONSTRUCTORS ***/
/*Gameplan new_gameplan () {
    Cell c[8];
    Gameplan gp;
    int i, k;
    for (i = 0; i < 8; i++)
        for (k = 0; k < 126; k++)
            gp.c[i][k] = new_cell_la(k, i, 0, 0);
    return gp;
}*/
/*** FUNCTIONS ***/
void gameplan_addShape (Gameplan *gp, Shape *s) {
    int i;
    for (i = 0; i < 4; i++)
        gp->c[s->y][s->x].a = 1;
}