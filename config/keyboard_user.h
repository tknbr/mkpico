// User keyboard definition: rows, cols, layers, etc
#include "keyboard_internal.h"

// device, col/row, index, gpio
#define SPLITS 2

#define KEYBOARD_GPIO_MAPPING      \ 
    X(0,    COL,    0,     5)      \
    X(0,    COL,    1,     6)      \    
    X(0,    COL,    2,     7)      \
    X(0,    COL,    3,     9)      \
    X(0,    COL,    4,    10)      \
    X(0,    ROW,    0,    11)      \
    X(0,    ROW,    1,    12)      \
    X(0,    ROW,    2,    13)      \
    X(0,    ROW,    3,    14)      \
    X(1,    COL,    0,    28)      \
    X(1,    COL,    1,    27)      \    
    X(1,    COL,    2,    26)      \
    X(1,    COL,    3,    22)      \
    X(1,    COL,    4,    21)      \
    X(1,    ROW,    0,    20)      \
    X(1,    ROW,    1,    19)      \
    X(1,    ROW,    2,    18)      \
    X(1,    ROW,    3,    17)      \


// device, layer, col, row, value
#define KEYBOARD_LAYOUT           \
    X(0, 0, 0, 0, 'q')            \
    X(0, 0, 1, 0, 'w')            \
    X(0, 0, 2, 0, 'e')            \ 
    X(0, 0, 3, 0, 'r')            \
    X(0, 0, 4, 0, 't')            \
