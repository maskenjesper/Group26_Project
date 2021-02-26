#include <stdlib.h>
#include <stdint.h>
#include "obj.h"

/**************** CELL  ****************/
/*** CONSTRUCTORS ***/
Cell new_cell (uint8_t x, uint8_t y, uint8_t a, uint8_t p) {
    Cell c = {.x = x, .y = y, .a = a, .p = p};
    return c;
}

/**************** SHAPE ****************/
/*** CONSTRUCTORS ***/
Shape new_shape (shape s, uint8_t x, uint8_t y, uint8_t a, uint8_t p) {
    Shape S = {.s = s, .x = x, .y = y, .a = a, .p = p};
    if (s == BOX) {
        S.c[0] = new_cell(x, y - 1, a, p);
        S.c[1] = new_cell(x, y, a, p);
        S.c[2] = new_cell(x + 3, y - 1, a, p);
        S.c[3] = new_cell(x + 3, y, a, p);
    }

    else if (s == STICK) {
        S.c[0] = new_cell(x, y - 1, a, p);
        S.c[1] = new_cell(x, y, a, p);
        S.c[2] = new_cell(x, y + 1, a, p);
        S.c[3] = new_cell(x, y + 2, a, p);
    }

    else if (s == T) {
        S.c[0] = new_cell(x, y - 1, a, p);
        S.c[1] = new_cell(x, y, a, p);
        S.c[2] = new_cell(x + 3, y, a, p);
        S.c[3] = new_cell(x, y + 1, a, p);
    }

    else if (s == LRIGHT) {
        S.c[0] = new_cell(x, y, a, p);
        S.c[1] = new_cell(x, y + 1, a, p);
        S.c[2] = new_cell(x + 3, y, a, p);
        S.c[3] = new_cell(x + 6, y, a, p);
    }

    else if (s == LLEFT) {
        S.c[0] = new_cell(x, y - 1, a, p);
        S.c[1] = new_cell(x, y, a, p);
        S.c[2] = new_cell(x + 3, y, a, p);
        S.c[3] = new_cell(x + 6, y, a, p);
    }

    else if (s == ZRIGHT) {
        S.c[0] = new_cell(x, y - 1, a, p);
        S.c[1] = new_cell(x, y, a, p);
        S.c[2] = new_cell(x + 3, y, a, p);
        S.c[3] = new_cell(x + 3, y + 1, a, p);
    }

    else {
        S.c[0] = new_cell(x + 3, y - 1, a, p);
        S.c[1] = new_cell(x, y, a, p);
        S.c[2] = new_cell(x + 3, y, a, p);
        S.c[3] = new_cell(x, y + 1, a, p);
    }
    return S;
}

/**************** CellContainer ****************/
/*** Initialization ***/
void init_cellcontainer (CellContainer cc) {
    int i;
    for (i = 0; i < CELLCONTAINER_LENGTH; i++)
        cc.cells[i] = new_cell(0, 0, 0, 0);
}
/*** FUNCTIONS ***/
void cellcontainer_addCell(CellContainer *cc, Cell *c) {
    int i;
    for (i = 0; i < CELLCONTAINER_LENGTH; i++)
        if (cc->cells[i].a == 0)
            cc->cells[i] = *c;
}
void cellcontainer_removeCell(CellContainer *cc, Cell *c) {
    int i;
    for (i = 0; i < CELLCONTAINER_LENGTH; i++)
        if (&cc->cells[i] == c)
            cc->cells[i].a = 0;
}
void cellcontainer_addShape(CellContainer *cc, Shape *s) {
    int i;
    for (i = 0; i < 4; i++)
        cellcontainer_addCell(cc, &s->c[i]);
}