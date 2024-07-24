#include "compile.h"
#include "keymap.h"

#ifndef _GPIOS_H
#define _GPIOS_H


/** -------------------------
 *      Modify GPIO pins
 *  -------------------------
 */

#if defined(ROLE_MASTER)
uint8_t columns_gpios[NUM_COLS] = {5, 6, 7, 9, 10};
uint8_t rows_gpios[NUM_ROWS]    = {11, 12, 13, 14};
#endif

#if defined(ROLE_SLAVE)
uint8_t columns_gpios[NUM_COLS] = {21, 22, 26, 27, 28};
uint8_t rows_gpios[NUM_ROWS]    = {20, 19, 18, 17};

#define COL_OFFSET 5

#endif

#endif // GPIOS
