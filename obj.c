#include <stdlib.h>
#include <stdint.h>
#include "obj.h"

/**************** CELL CONSTRUCTORS ****************/
/*  Each version of the constructor sets each field as either parameter value (for those with parameters)
    or 0. */
struct Cell new_cell () {
    struct Cell c = {.x = 0, .y = 0, .a = 0, .p = 0};
    return c;
}
struct Cell new_cell_lc (uint8_t x, uint8_t y) {
    struct Cell c = {.x = x, .y = y, .a = 0, .p = 0};
    return c;
}
struct Cell new_cell_la (uint8_t x, uint8_t y, uint8_t a, uint8_t p) {
    struct Cell c = {.x = x, .y = y, .a = a, .p = p};
    return c;
}

/**************** SHAPE CONSTRUCTORS ****************/
/*  Each version of the constructor sets each field as either parameter value (for those with parameters)
    or 0. */
struct Shape new_shape (enum shape s) {
    struct Shape S = {.s = s, .x = 0, .y = 1, .a = 0, .p = 0};
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
struct Shape new_shape_lc (enum shape s, uint8_t x, uint8_t y) {
    struct Shape S = {.s = s, .x = x, .y = y, .a = 0, .p = 0};
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
struct Shape new_shape_la (enum shape s, uint8_t x, uint8_t y, uint8_t a, uint8_t p) {
    struct Shape S = {.s = s, .x = x, .y = y, .a = a, .p = p};
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
