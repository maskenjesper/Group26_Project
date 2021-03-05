#pragma once

/**************** CELL OBJECT ****************/
/*
    Fields:
    x: x-coordinate, range (0-125)
    y: y-coordinate, range (0-7)
    a: active, (true/false)
    p: player, (1,2) */
typedef struct Cell {
    uint8_t x, y, a, p;
    uint16_t id;
} Cell;
Cell new_cell(uint8_t x, uint8_t y, uint8_t a, uint8_t p);

/**************** SHAPE OBJECT ****************/
/*
    Fields:
    x: centercell[1] x-coordinate, range (0-125)
    y: centercell[1] y-coordinate, range (0-7)
    a: active, (true/false)
    p: player, (1,2)
    s: type of shape
    c: instances of cells with relative position[2]
    
    [1]:    Centercell is the cell that is as in the middle as possible. Jakob has 
            physical diagrams of which cell is center for each type of shape.
    [2]:    The cells positions are relative to the shapes coordinate i.e the
            centercell, one of the cells is the centercell. */
typedef enum shape {BOX, STICK, T, LRIGHT, LLEFT, ZRIGHT, ZLEFT} shape;
typedef struct Shape {
    uint8_t a, p, r;
    shape s;
    Cell c[4];
} Shape;
Shape new_shape(shape, uint8_t x, uint8_t y, uint8_t a, uint8_t p);

/**************** CELLCONTAINER OBJECT ****************/
/*
     */
#define CELLCONTAINER_LENGTH 810
typedef struct CellContainer {
    Cell cells[CELLCONTAINER_LENGTH];
} CellContainer;
typedef enum DIR {UP, DOWN, RIGHT, LEFT} DIR;
void init_cellcontainer (CellContainer *cc);
void cellcontainer_addCell(CellContainer *cc, Cell *c);
void cellcontainer_removeCell(CellContainer *cc, Cell *c);
void cellcontainer_moveCell (CellContainer *cc, Cell *c, DIR d);
void cellcontainer_updateCell (CellContainer *cc, Cell *c);
int cellcontainer_cellCheckCollision (CellContainer *cc, Cell *c, DIR d);
void cellcontainer_addShape(CellContainer *cc, Shape *s);
void cellcontainer_removeShape (CellContainer *cc, Shape *s);
int cellcontainer_moveShape(CellContainer *cc, Shape *s, DIR d);
void cellcontainer_rotateShape (CellContainer *cc, Shape *s);
int cellcontainer_checkShapeOverlapping (CellContainer *cc, Shape *s);
int cellcontainer_scanForRows (CellContainer *cc);
int cellcontainer_cellAtPos (CellContainer *cc, uint8_t x, uint8_t y);
void cellcontainer_removeRow (CellContainer *cc, uint8_t x);

/**************** SCORE OBJECT ****************/
/*
    */
typedef struct ScoreInitialsPair {
    char c1, c2;
    int score;
} ScoreInitialsPair;