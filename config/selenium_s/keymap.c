
#include "keymap.h"


uint8_t keymap[][NUM_ROWS][NUM_COLS] = {
	/*
	 *
	 * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
	 * │ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │
	 * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
	 * │ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │
	 * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
	 * │ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │
 	 * └───┴───┴───┼───┼───┤       ├───┼───┼───┴───┴───┘
	 *             │Bsp│Tab│       │Spc│Ent│
	 *             └───┴───┘       └───┴───┘ 
	 *
	 */
	[0] = LAYOUT_SELENIUM_S(
	   K_Q,    K_W,    K_E,    K_R,    K_T,         K_Y,    K_U,    K_I,    K_O,   K_P,
	   K_A,    K_S,    K_D,    K_F,    K_G,         K_H,    K_J,    K_K,    K_L,   K_SCLN,
	   K_Z,    K_X,    K_C,    K_V,    K_B,         K_N,    K_M,    K_COMM, K_DOT, K_SLSH,
							   K_BSPC, K_TAB,       K_SPC,  K_ENT
	)
};


size_t keymap_layers = sizeof(keymap) / sizeof(keymap[0]);
