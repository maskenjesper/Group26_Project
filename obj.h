#pragma once

/**************** CELL OBJECT ****************/
/*
    Fields:
    x: x-coordinate, range (0-126)
    y: y-coordinate, range (0-7)
    a: active, (true/false)
    p: player, (0,1) */
struct Cell {
    uint8_t x, y, a, p;
};
struct Cell new_cell ();
struct Cell new_cell_lc(uint8_t x, uint8_t y);
struct Cell new_cell_la(uint8_t x, uint8_t y, uint8_t a, uint8_t p);
typedef struct Cell Cell;

/**************** SHAPE OBJECT ****************/
/*
    Fields:
    x: centercell[1] x-coordinate, range (0-126)
    y: centercell[1] y-coordinate, range (0-7)
    a: active, (true/false)
    p: player, (0,1)
    s: type of shape
    c: instances of cells with relative position[2]
    
    [1]:    Centercell is the cell that is as in the middle as possible. Jakob has 
            physical diagrams of which cell is center for each type of shape.
    [2]:    The cells positions are relative to the shapes coordinate i.e the
            centercell, one of the cells is the centercell. */
enum shape {BOX, STICK, T, LRIGHT, LLEFT, ZRIGHT, ZLEFT};
struct Shape {
    uint8_t x, y, a, p;
    enum shape s;
    struct Cell c[4];
};
struct Shape new_shape (enum shape);
struct Shape new_shape_lc(enum shape, uint8_t x, uint8_t y);
struct Shape new_shape_la(enum shape, uint8_t x, uint8_t y, uint8_t a, uint8_t p);
typedef struct Shape Shape;
