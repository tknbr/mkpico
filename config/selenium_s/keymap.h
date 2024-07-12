
#ifndef _KEYMAP_H
#define _KEYMAP_H

#include "keys.h"


#define NUM_ROWS 4
#define NUM_COLS 10

#define NUM_ROWS_SPLIT 4
#define NUM_COLS_SPLIT 5

#define LAYOUT_SELENIUM_S( \
        L01, L02, L03, L04, L05,      R01, R02, R03, R04, R05, \
        L06, L07, L08, L09, L10,      R06, R07, R08, R09, R10, \
        L11, L12, L13, L14, L15,      R11, R12, R13, R14, R15, \
                       L16, L17,      R16, R17                 \
        ) \
        { \
            { L01, L02, L03, L04, L05, R01, R02, R03, R04, R05 }, \
            { L06, L07, L08, L09, L10, R06, R07, R08, R09, R10 }, \
            { L11, L12, L13, L14, L15, R11, R12, R13, R14, R15 }, \
            { K_NO, K_NO, K_NO, L16, L17, R16, R17, K_NO, K_NO, K_NO } \
        }

#endif