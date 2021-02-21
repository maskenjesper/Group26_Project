#pragma once

struct Cell {
    uint8_t x, y, a, p;
};
struct Cell new_cell ();
struct Cell new_cell_lc(uint8_t x, uint8_t y);
struct Cell new_cell_la(uint8_t x, uint8_t y, uint8_t a, uint8_t p);

enum shape {BOX, STICK, T, LRIGHT, LLEFT, ZRIGHT, ZLEFT};
struct Shape {
    uint8_t x, y, a, p;
    enum shape s;
    struct Cell c[4];
};
struct Shape new_shape (enum shape);
struct Shape new_shape_lc(enum shape, uint8_t x, uint8_t y);
struct Shape new_shape_la(enum shape, uint8_t x, uint8_t y, uint8_t a, uint8_t p);
