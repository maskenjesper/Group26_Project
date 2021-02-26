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
} Cell;
Cell new_cell ();
Cell new_cell_lc(uint8_t x, uint8_t y);
Cell new_cell_la(uint8_t x, uint8_t y, uint8_t a, uint8_t p);

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
    uint8_t x, y, a, p;
    shape s;
    Cell c[4];
} Shape;
Shape new_shape (shape);
Shape new_shape_lc(shape, uint8_t x, uint8_t y);
Shape new_shape_la(shape, uint8_t x, uint8_t y, uint8_t a, uint8_t p);

/**************** CellContainer OBJECT ****************/
/*
     */
#define CELLCONTAINER_LENGTH 100
typedef struct CellContainer {
    Cell cells[CELLCONTAINER_LENGTH];
} CellContainer;
CellContainer new_cellcontainer ();

/**************** Gameplan OBJECT ****************/
/*
     */
    /*#define GAMEPLAN_PIXEL_WIDTH 126
#define GAMEPLAN_PIXEL_HEIGHT 8
typedef struct Gameplan {
    Cell c[GAMEPLAN_PIXEL_HEIGHT][GAMEPLAN_PIXEL_WIDTH];
} Gameplan;
Gameplan new_gameplan ();
void gameplan_addShape (Gameplan *gp, Shape *s);*/
