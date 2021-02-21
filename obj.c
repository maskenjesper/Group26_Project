#include <stdlib.h>
#include "obj.h"

struct cell {
    uint8_t x, y;
};

/*cell* cell_new (uint8_t x, uint8_t y) {
    cell* p = malloc(sizeof(cell));
    p->x = x;
    p->y = y;
    return p;
}*/

struct gameplan {
    char cells[8][40];  // [row][column]
};

struct shape_box {                                 ////
    uint8_t cells[8][40];                          ////
};

struct shape_stick {                              ////////
    uint8_t cells[8][40];      
};

struct shape_t {                                   //////
    uint8_t cells[8][40];                            //
};

struct shape_lRight {                                //
    uint8_t cells[8][40];                            //
};                                                   ////

struct shape_lLeft {                                 //
    uint8_t cells[8][40];                            //
};                                                 ////

struct shape_zRight {                                ////
    uint8_t cells[8][40];                          ////
};

struct shape_zLeft {                             ////
    char cells[8][40];                             ////
}; 
