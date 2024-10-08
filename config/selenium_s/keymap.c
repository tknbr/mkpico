
#include "keymap.h"


uint8_t keymap[][NUM_ROWS][NUM_COLS] = {
    /*
     *
     * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
     * │ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │
     * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │ G │       │ H │ J │ K │ L │Ent│
     * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B │       │ N │ M │Alt│Ctr│Shf│
     * └───┴───┴───┼───┼───┤       ├───┼───┼───┴───┴───┘
     *             │Bsp│LUp│       │Spc│LDw│
     *             └───┴───┘       └───┴───┘ 
     *
     */
    [0] = LAYOUT_SELENIUM_S(
       K_Q,    K_W,    K_E,    K_R,    K_T,         K_Y,    K_U,    K_I,    K_O,   K_P,
       K_A,    K_S,    K_D,    K_F,    K_G,         K_H,    K_J,    K_K,    K_L,   K_ENT,
       K_Z,    K_X,    K_C,    K_V,    K_B,         K_N,    K_M,    K_ALT,  K_CTRL,K_SHFT,
                               K_BSPC, K_LYRUP,     K_SPC,  K_LYRDWN
    ),
    /*
     *
     * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
     * │ESC│ ' │ UP│ [ │ ] │       │ 7 │ 8 │ 9 │ - │ / │
     * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
     * │TAB│LFT│DWN│RGT│ # │       │ 4 │ 5 │ 6 │ = │Ent│
     * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
     * │Shf│ \ │ ; │ , │ . │       │ 1 │ 2 │ 3 │Alt│Shf│
     * └───┴───┴───┼───┼───┤       ├───┼───┼───┴───┴───┘
     *             │Bsp│LUp│       │ 0 │LDw│
     *             └───┴───┘       └───┴───┘ 
     *
     */
    [1] = LAYOUT_SELENIUM_S(
       K_ESC,  K_APOS, K_A_U,  K_BRAL, K_BRAR,      K_7,    K_8,    K_9,    K_MIN, K_SLSH,
       K_TAB,  K_A_L,  K_A_D,  K_A_R,  K_HASH,      K_4,    K_5,    K_6,    K_EQU, K_ENT,
       K_SHFT, K_BKSL, K_SCLN, K_COMM, K_DOT,       K_1,    K_2,    K_3,    K_ALT, K_SHFT,
                               K_BSPC, K_LYRUP,     K_0,    K_LYRDWN
    )
};

size_t keymap_layers = sizeof(keymap) / sizeof(keymap[0]);
