#include <stdint.h>

typedef struct cell {
    uint8_t pixels[3][3];
    uint8_t marked;
} cell;

typedef struct gameplan {
    char cells[8][40];  // [row][column]
} gameplan;

typedef struct shape_box {                      ////
    char cells[8][40];                          ////
} shape_box;

typedef struct shape_stick {                    ////////
    char cells[8][40];      
} shape_stick;

typedef struct shape_t {                        //////
    char cells[8][40];                            //
} shape_t;

typedef struct shape_lRight {                     //
    char cells[8][40];                            //
} shape_lRight;                                   ////

typedef struct shape_lLeft {                      //
    char cells[8][40];                            //
} shape_lLeft;                                  ////

typedef struct shape_zRight {                     ////
    char cells[8][40];                          ////
} shape_zRight;

typedef struct shape_zLeft {                    ////
    char cells[8][40];                            ////
} shape_zLeft;