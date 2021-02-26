#include <stdlib.h>
#include <stdint.h>
#include "obj.h"

/**************** CELL  ****************/
/*** CONSTRUCTORS ***/
Cell new_cell (uint8_t x, uint8_t y, uint8_t a, uint8_t p, uint16_t id) {
    Cell c = {.x = x, .y = y, .a = a, .p = p, .id = id};
    return c;
}

/**************** SHAPE ****************/
/*** CONSTRUCTORS ***/
Shape new_shape (shape s, uint8_t x, uint8_t y, uint8_t a, uint8_t p, uint16_t id) {
    Shape S = {.s = s, .x = x, .y = y, .a = a, .p = p};
    if (s == BOX) {
        S.c[0] = new_cell(x, y - 1, a, p, id++);
        S.c[1] = new_cell(x, y, a, p, id++);
        S.c[2] = new_cell(x + 3, y - 1, a, p, id++);
        S.c[3] = new_cell(x + 3, y, a, p, id++);
    }

    else if (s == STICK) {
        S.c[0] = new_cell(x, y - 1, a, p, id++);
        S.c[1] = new_cell(x, y, a, p, id++);
        S.c[2] = new_cell(x, y + 1, a, p, id++);
        S.c[3] = new_cell(x, y + 2, a, p, id++);
    }

    else if (s == T) {
        S.c[0] = new_cell(x, y - 1, a, p, id++);
        S.c[1] = new_cell(x, y, a, p, id++);
        S.c[2] = new_cell(x + 3, y, a, p, id++);
        S.c[3] = new_cell(x, y + 1, a, p, id++);
    }

    else if (s == LRIGHT) {
        S.c[0] = new_cell(x, y, a, p, id++);
        S.c[1] = new_cell(x, y + 1, a, p, id++);
        S.c[2] = new_cell(x + 3, y, a, p, id++);
        S.c[3] = new_cell(x + 6, y, a, p, id++);
    }

    else if (s == LLEFT) {
        S.c[0] = new_cell(x, y - 1, a, p, id++);
        S.c[1] = new_cell(x, y, a, p, id++);
        S.c[2] = new_cell(x + 3, y, a, p, id++);
        S.c[3] = new_cell(x + 6, y, a, p, id++);
    }

    else if (s == ZRIGHT) {
        S.c[0] = new_cell(x, y - 1, a, p, id++);
        S.c[1] = new_cell(x, y, a, p, id++);
        S.c[2] = new_cell(x + 3, y, a, p, id++);
        S.c[3] = new_cell(x + 3, y + 1, a, p, id++);
    }

    else {
        S.c[0] = new_cell(x + 3, y - 1, a, p, id++);
        S.c[1] = new_cell(x, y, a, p, id++);
        S.c[2] = new_cell(x + 3, y, a, p, id++);
        S.c[3] = new_cell(x, y + 1, a, p, id++);
    }
    return S;
}

/**************** CELLCONTAINER ****************/
/*** INITIALIZATION ***/
void init_cellcontainer (CellContainer cc) {
    int i;
    for (i = 0; i < CELLCONTAINER_LENGTH; i++)
        cc.cells[i] = new_cell(0, 0, 0, 0, 0);
}
/*** FUNCTIONS ***/
void cellcontainer_addCell(CellContainer *cc, Cell *c) {
    int i;
    for (i = 0; i < CELLCONTAINER_LENGTH; i++)
        if (cc->cells[i].a == 0) {
            cc->cells[i] = *c;
            break;
        }
}
void cellcontainer_removeCell(CellContainer *cc, Cell *c) {
    int i;
    for (i = 0; i < CELLCONTAINER_LENGTH; i++)
        if (cc->cells[i].id == c->id) {
            cc->cells[i].a = 0;
            break;
        }
}
void cellcontainer_addShape(CellContainer *cc, Shape *s) {
    int i;
    for (i = 0; i < 4; i++)
        cellcontainer_addCell(cc, &s->c[i]);
}

void cellcontainer_moveShape(CellContainer *cc, Shape *s, DIR d) {
    int i;
    if (d == UP)
        for (i = 0; i < 4; i++) {
            cellcontainer_removeCell(cc, &s->c[i]);
            s->c[i].y = s->c[i].y - 1;
            cellcontainer_addCell(cc, &s->c[i]);
        }
    else if (d == DOWN)
        for (i = 0; i < 4; i++) {
            cellcontainer_removeCell(cc, &s->c[i]);
            s->c[i].y = s->c[i].y + 1;
            cellcontainer_addCell(cc, &s->c[i]);
        }
    else if (d == RIGHT)
        for (i = 0; i < 4; i++) {
            cellcontainer_removeCell(cc, &s->c[i]);
            s->c[i].x = s->c[i].x + 1;
            cellcontainer_addCell(cc, &s->c[i]);
        }
    else 
        for (i = 0; i < 4; i++) {
            cellcontainer_removeCell(cc, &s->c[i]);
            s->c[i].x = s->c[i].x - 1;
            cellcontainer_addCell(cc, &s->c[i]);
        }
}