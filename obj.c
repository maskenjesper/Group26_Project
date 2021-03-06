#include <stdlib.h>
#include <stdint.h>
#include "obj.h"
#include "lib.h"

/**************** CELL  ****************/
/*** CONSTRUCTORS ***/
Cell new_cell (uint8_t x, uint8_t y, uint8_t a, uint8_t p) {
    Cell c = {.x = x, .y = y, .a = a, .p = p, .id = idcount++};
    return c;
}

/**************** SHAPE ****************/
/*** CONSTRUCTORS ***/
Shape new_shape (shape s, uint8_t x, uint8_t y, uint8_t a, uint8_t p) {
    Shape S = {.s = s, .a = a, .p = p};
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

/**************** CELLCONTAINER ****************/
/*** INITIALIZATION ***/
void init_cellcontainer (CellContainer *cc) {
    int i;
    for (i = 0; i < CELLCONTAINER_LENGTH; i++)
        cc->cells[i] = new_cell(0, 0, 0, 0);
}
/*** FUNCTIONS ***/
void cellcontainer_addCell (CellContainer *cc, Cell *c) {
    int i;
    for (i = 0; i < CELLCONTAINER_LENGTH; i++)
        if (cc->cells[i].a == 0) {
            cc->cells[i] = *c;
            break;
        }
}
void cellcontainer_removeCell (CellContainer *cc, Cell *c) {
    int i;
    for (i = 0; i < CELLCONTAINER_LENGTH; i++)
        if (cc->cells[i].id == c->id) {
            cc->cells[i] = new_cell(0, 0, 0, 0);
            break;
        }
}
void cellcontainer_moveCell (CellContainer *cc, Cell *c, DIR d) {
    if (d == UP)
        c->y -= 1;
    else if (d == DOWN)
        c->y += 1;
    else if (d == RIGHT)
        c->x += 1;
    else   
        c->x -= 1;
    cellcontainer_updateCell(cc, c);
}
void cellcontainer_updateCell (CellContainer *cc, Cell *c) {
    int i;
    for (i = 0; i < CELLCONTAINER_LENGTH; i++)
        if (cc->cells[i].id == c->id) {
            cc->cells[i] = *c;
            break;
        }
}
int cellcontainer_cellCheckCollision (CellContainer *cc, Cell *c, DIR d) {
    int i;
    if (d == UP && c->y == GAMEPLAN_Y1 ||
        d == DOWN && c->y == GAMEPLAN_Y2 / 3 - 1||
        d == RIGHT && c->x == GAMEPLAN_X2 - 3 ||
        d == LEFT && c->x == GAMEPLAN_X1) {
        return 1;
        }
    else if (d == RIGHT) {
        for (i = 0; i < CELLCONTAINER_LENGTH; i++) {
            if (cc->cells[i].p == 0) {
                if (cc->cells[i].x == c->x + 3 && cc->cells[i].y == c->y) {
                    return 1;
                }
            }
        }
    }
    else if (d == LEFT) {
        for (i = 0; i < CELLCONTAINER_LENGTH; i++) {
            if (cc->cells[i].p == 0) {
                if (cc->cells[i].x == c->x - 3 && cc->cells[i].y == c->y) {
                    return 1;
                }
            }
        }
    }
    else if (d == UP) {
        for (i = 0; i < CELLCONTAINER_LENGTH; i++) {
            if (cc->cells[i].p == 0) {
                if ((   cc->cells[i].x == c->x || 
                        cc->cells[i].x == c->x + 1 || 
                        cc->cells[i].x == c->x + 2 ||
                        cc->cells[i].x == c->x - 1 ||
                        cc->cells[i].x == c->x - 2) && 
                        cc->cells[i].y == c->y - 1) {
                    return 1;
                }
            }
        }
    }
    else if (d == DOWN) {
        for (i = 0; i < CELLCONTAINER_LENGTH; i++) {
            if (cc->cells[i].p == 0) {
                if ((   cc->cells[i].x == c->x || 
                        cc->cells[i].x == c->x + 1 || 
                        cc->cells[i].x == c->x + 2 ||
                        cc->cells[i].x == c->x - 1 ||
                        cc->cells[i].x == c->x - 2) && 
                        cc->cells[i].y == c->y + 1) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
void cellcontainer_addShape (CellContainer *cc, Shape *s) {
    int i;
    for (i = 0; i < 4; i++)
        cellcontainer_addCell(cc, &s->c[i]);
}
void cellcontainer_removeShape (CellContainer *cc, Shape *s) {
    int i;
    for (i = 0; i < 4; i++)
        cellcontainer_removeCell(cc, &s->c[i]);
}
int cellcontainer_moveShape (CellContainer *cc, Shape *s, DIR d) {
    int i;
    for (i = 0; i < 4; i++) {
        s->c[i].p = 1;
        cellcontainer_updateCell(cc, &s->c[i]);
    }
    for (i = 0; i < 4; i++)
        if (cellcontainer_cellCheckCollision(cc, &s->c[i], d)) {
            for (i = 0; i < 4; i++) {
                s->c[i].p = 0;
                cellcontainer_updateCell(cc, &s->c[i]);
            }
            return 1;
        }
    for (i = 0; i < 4; i++)
        cellcontainer_moveCell(cc, &s->c[i], d);
    for (i = 0; i < 4; i++) {
        s->c[i].p = 0;
        cellcontainer_updateCell(cc, &s->c[i]);
    }
    return 0;
}
void cellcontainer_rotateShape (CellContainer *cc, Shape *s) {
    if (s->s == BOX)
        return;
    Shape tempShape = *s;
    int i;
    for (i = 0; i < 4; i++) {
        s->c[i].p = 1;
        tempShape.c[i] = s->c[i];
        cellcontainer_updateCell(cc, &s->c[i]);
    }
    if (s->s == STICK) {
        if (s->r == 0) {
            tempShape.c[0].y += 1;
            tempShape.c[0].x -= 3;

            tempShape.c[2].y -= 1;
            tempShape.c[2].x += 3;

            tempShape.c[3].y -= 2;
            tempShape.c[3].x += 6;
        }
        else if (s->r == 1) {
            tempShape.c[0].y += 1;
            tempShape.c[0].x += 3;

            tempShape.c[2].y -= 1;
            tempShape.c[2].x -= 3;

            tempShape.c[3].y -= 2;
            tempShape.c[3].x -= 6;
        }
        else if (s->r == 2) {
            tempShape.c[0].y -= 1;
            tempShape.c[0].x += 3;

            tempShape.c[2].y += 1;
            tempShape.c[2].x -= 3;

            tempShape.c[3].y += 2;
            tempShape.c[3].x -= 6;
        }
        else if (s->r == 3) {
            tempShape.c[0].y -= 1;
            tempShape.c[0].x -= 3;

            tempShape.c[2].y += 1;
            tempShape.c[2].x += 3;

            tempShape.c[3].y += 2;
            tempShape.c[3].x += 6;
        }
    }

    else if (s->s == T) {
        if (s->r == 0) {
            tempShape.c[0].y += 1;
            tempShape.c[0].x -= 3;

            tempShape.c[2].y -= 1;
            tempShape.c[2].x -= 3;

            tempShape.c[3].y -= 1;
            tempShape.c[3].x += 3;
        }
        else if (s->r == 1) {
            tempShape.c[0].y += 1;
            tempShape.c[0].x += 3;

            tempShape.c[2].y += 1;
            tempShape.c[2].x -= 3;

            tempShape.c[3].y -= 1;
            tempShape.c[3].x -= 3;
        }
        else if (s->r == 2) {
            tempShape.c[0].y -= 1;
            tempShape.c[0].x += 3;

            tempShape.c[2].y += 1;
            tempShape.c[2].x += 3;

            tempShape.c[3].y += 1;
            tempShape.c[3].x -= 3;
        }
        else if (s->r == 3) {
            tempShape.c[0].y -= 1;
            tempShape.c[0].x -= 3;

            tempShape.c[2].y -= 1;
            tempShape.c[2].x += 3;

            tempShape.c[3].y += 1;
            tempShape.c[3].x += 3;
        }
    }

    else if (s->s == LRIGHT) {
        if (s->r == 0) {
            tempShape.c[1].y -= 1;
            tempShape.c[1].x += 3;

            tempShape.c[2].y -= 1;
            tempShape.c[2].x -= 3;

            tempShape.c[3].y -= 2;
            tempShape.c[3].x -= 6;
        }
        else if (s->r == 1) {
            tempShape.c[1].y -= 1;
            tempShape.c[1].x -= 3;

            tempShape.c[2].y += 1;
            tempShape.c[2].x -= 3;

            tempShape.c[3].y += 2;
            tempShape.c[3].x -= 6;
        }
        else if (s->r == 2) {
            tempShape.c[1].y += 1;
            tempShape.c[1].x -= 3;

            tempShape.c[2].y += 1;
            tempShape.c[2].x += 3;

            tempShape.c[3].y += 2;
            tempShape.c[3].x += 6;
        }
        else if (s->r == 3) {
            tempShape.c[1].y += 1;
            tempShape.c[1].x += 3;

            tempShape.c[2].y -= 1;
            tempShape.c[2].x += 3;

            tempShape.c[3].y -= 2;
            tempShape.c[3].x += 6;
        }
    }

    else if (s->s == LLEFT) {
        if (s->r == 0) {
            tempShape.c[0].y += 1;
            tempShape.c[0].x -= 3;

            tempShape.c[2].y -= 1;
            tempShape.c[2].x -= 3;

            tempShape.c[3].y -= 2;
            tempShape.c[3].x -= 6;
        }
        else if (s->r == 1) {
            tempShape.c[0].y += 1;
            tempShape.c[0].x += 3;

            tempShape.c[2].y += 1;
            tempShape.c[2].x -= 3;

            tempShape.c[3].y += 2;
            tempShape.c[3].x -= 6;
        }
        else if (s->r == 2) {
            tempShape.c[0].y -= 1;
            tempShape.c[0].x += 3;

            tempShape.c[2].y += 1;
            tempShape.c[2].x += 3;

            tempShape.c[3].y += 2;
            tempShape.c[3].x += 6;
        }
        else if (s->r == 3) {
            tempShape.c[0].y -= 1;
            tempShape.c[0].x -= 3;

            tempShape.c[2].y -= 1;
            tempShape.c[2].x += 3;

            tempShape.c[3].y -= 2;
            tempShape.c[3].x += 6;
        }
    }

    else if (s->s == ZRIGHT) {
        if (s->r == 0) {
            tempShape.c[0].y += 1;
            tempShape.c[0].x -= 3;

            tempShape.c[2].y -= 1;
            tempShape.c[2].x -= 3;

            tempShape.c[3].y -= 2;
        }
        else if (s->r == 1) {
            tempShape.c[0].y += 1;
            tempShape.c[0].x += 3;

            tempShape.c[2].y += 1;
            tempShape.c[2].x -= 3;

            tempShape.c[3].x -= 6;
        }
        else if (s->r == 2) {
            tempShape.c[0].y -= 1;
            tempShape.c[0].x += 3;

            tempShape.c[2].y += 1;
            tempShape.c[2].x += 3;

            tempShape.c[3].y += 2;
        }
        else if (s->r == 3) {
            tempShape.c[0].y -= 1;
            tempShape.c[0].x -= 3;

            tempShape.c[2].y -= 1;
            tempShape.c[2].x += 3;

            tempShape.c[3].x += 6;
        }
    }

    else {
        if (s->r == 0) {
            tempShape.c[0].x -= 6;

            tempShape.c[2].y -= 1;
            tempShape.c[2].x -= 3;

            tempShape.c[3].y -= 1;
            tempShape.c[3].x += 3;
        }
        else if (s->r == 1) {
            tempShape.c[0].y += 2;

            tempShape.c[2].y += 1;
            tempShape.c[2].x -= 3;

            tempShape.c[3].y -= 1;
            tempShape.c[3].x -= 3;
        }
        else if (s->r == 2) {
            tempShape.c[0].x += 6;

            tempShape.c[2].y += 1;
            tempShape.c[2].x += 3;

            tempShape.c[3].y += 1;
            tempShape.c[3].x -= 3;
        }
        else if (s->r == 3) {
            tempShape.c[0].y -= 2;

            tempShape.c[2].y -= 1;
            tempShape.c[2].x += 3;

            tempShape.c[3].y += 1;
            tempShape.c[3].x += 3;
        }
    }

    // Try to adjust for collision
    if (cellcontainer_checkShapeOverlapping(cc, &tempShape)) {
        for (i = 0; i < 4; i++)
            tempShape.c[i].y++;
        if (cellcontainer_checkShapeOverlapping(cc, &tempShape))
            for (i = 0; i < 4; i++)
                tempShape.c[i].y++;
    }
    if (cellcontainer_checkShapeOverlapping(cc, &tempShape)) {
        for (i = 0; i < 4; i++)
            tempShape.c[i].y -= 3;
        if (cellcontainer_checkShapeOverlapping(cc, &tempShape)) {
            for (i = 0; i < 4; i++)
                tempShape.c[i].y--;
            if (cellcontainer_checkShapeOverlapping(cc, &tempShape)) {
                for (i = 0; i < 4; i++) {
                    s->c[i].p = 0;
                    cellcontainer_updateCell(cc, &s->c[i]);
                }
                return;
            }
        }
    }

    // wrapping up
    if (s->r == 3)
        s->r = 0;
    else
        s->r++;
    for (i = 0; i < 4; i++) {
        s->c[i].p = 0;
        s->c[i] = tempShape.c[i];
        cellcontainer_updateCell(cc, &s->c[i]);
    }
}
int cellcontainer_checkShapeOverlapping (CellContainer *cc, Shape *s) {
    int i, k, m;
    for (i = 0; i < 4; i++) {
        /***** Boundry collisioncheck *****/
        if (s->c[i].y < GAMEPLAN_Y1 ||
            s->c[i].x < GAMEPLAN_X1 ||
            s->c[i].y >= GAMEPLAN_Y2 / 3 || 
            s->c[i].x > GAMEPLAN_X2 - 2) {
            return 1;
        }
        /***** Cell collisioncheck *****/
        for (k = 0; k < CELLCONTAINER_LENGTH; k++) {
            if (cc->cells[k].p == 0 &&
                cc->cells[k].a == 1 && 
                (cc->cells[k].x == s->c[i].x || 
                cc->cells[k].x == s->c[i].x + 1 || 
                cc->cells[k].x == s->c[i].x + 2 || 
                cc->cells[k].x == s->c[i].x - 1 || 
                cc->cells[k].x == s->c[i].x - 2) && 
                cc->cells[k].y == s->c[i].y) {
                return 1;
            }
        }
    }
    return 0;
}
int cellcontainer_scanForRows (CellContainer *cc) {
    int x, y, m, n;
    
    Cell *cellptr[10];
    int row = 0;
    for (x = GAMEPLAN_X2 - 3; x >= 0; x -= 3) {
        if (cellcontainer_cellAtPos(cc, x, 0) &&
            cellcontainer_cellAtPos(cc, x, 1) &&
            cellcontainer_cellAtPos(cc, x, 2) &&
            cellcontainer_cellAtPos(cc, x, 3) &&
            cellcontainer_cellAtPos(cc, x, 4) &&
            cellcontainer_cellAtPos(cc, x, 5) &&
            cellcontainer_cellAtPos(cc, x, 6) &&
            cellcontainer_cellAtPos(cc, x, 7) &&
            cellcontainer_cellAtPos(cc, x, 8) &&
            cellcontainer_cellAtPos(cc, x, 9)) {
            cellcontainer_removeRow(cc, x);
            return 1 + cellcontainer_scanForRows(cc);
        }
    }
    return 0;
}
int cellcontainer_cellAtPos (CellContainer *cc, uint8_t x, uint8_t y) {
    int i;
    for (i = 0; i < CELLCONTAINER_LENGTH; i++) {
        if (cc->cells[i].a == 1 &&
            cc->cells[i].x == x &&
            cc->cells[i].y == y) {
            return 1;
        }
    }
}
void cellcontainer_removeRow (CellContainer *cc, uint8_t x) {
    int i, k, m;
    for (i = 0; i < GAMEPLAN_Y2 / 3; i++) {
        for (k = 0; k < CELLCONTAINER_LENGTH; k++) {
            if (cc->cells[k].a == 1 &&
                cc->cells[k].x == x &&
                cc->cells[k].y == i) {
                cellcontainer_removeCell(cc, &cc->cells[k]);
            }
        }
    }
    for (k = 0; k < CELLCONTAINER_LENGTH; k++) {
        if (cc->cells[k].a == 1 &&
            cc->cells[k].x < x ) {
            for (i = 0; i < 3; i++) {
                cellcontainer_moveCell(cc, &cc->cells[k], RIGHT);
            }
        }
    }
}