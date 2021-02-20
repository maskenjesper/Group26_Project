typedef struct cell {
    char pixels[3][3];
} cell;

typedef struct gameplan {
    char cells[8][40];  // [row][column]
}