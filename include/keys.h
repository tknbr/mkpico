
#ifndef KEYS_H
#define KEYS_H

#include "class/hid/hid_device.h" 

// Letters
#define K_A HID_KEY_A
#define K_B HID_KEY_B
#define K_C HID_KEY_C
#define K_D HID_KEY_D
#define K_E HID_KEY_E
#define K_F HID_KEY_F
#define K_G HID_KEY_G
#define K_H HID_KEY_H
#define K_I HID_KEY_I
#define K_J HID_KEY_J
#define K_K HID_KEY_K
#define K_L HID_KEY_L
#define K_M HID_KEY_M
#define K_N HID_KEY_N
#define K_O HID_KEY_O
#define K_P HID_KEY_P
#define K_Q HID_KEY_Q
#define K_R HID_KEY_R
#define K_S HID_KEY_S
#define K_T HID_KEY_T
#define K_U HID_KEY_U
#define K_V HID_KEY_V
#define K_W HID_KEY_W
#define K_X HID_KEY_X
#define K_Y HID_KEY_Y
#define K_Z HID_KEY_Z

#define K_BSPC HID_KEY_BACKSPACE
#define K_NO HID_KEY_SEMICOLON

// Numbers
#define K_0 HID_KEY_0
#define K_1 HID_KEY_1
#define K_2 HID_KEY_2
#define K_3 HID_KEY_3
#define K_4 HID_KEY_4
#define K_5 HID_KEY_5
#define K_6 HID_KEY_6
#define K_7 HID_KEY_7
#define K_8 HID_KEY_8
#define K_9 HID_KEY_9

// Arithmetic

#define K_MIN HID_KEY_MINUS
#define K_EQU HID_KEY_EQUAL


// Punctuation
#define K_TAB  HID_KEY_TAB
#define K_SPC  HID_KEY_SPACE
#define K_ENT  HID_KEY_ENTER
#define K_COMM HID_KEY_COMMA
#define K_DOT  HID_KEY_PERIOD
#define K_SLSH HID_KEY_SLASH
#define K_SCLN HID_KEY_SEMICOLON
#define K_BRAL HID_KEY_BRACKET_LEFT
#define K_BRAR HID_KEY_BRACKET_RIGHT
#define K_BKSL HID_KEY_BACKSLASH
#define K_HASH HID_KEY_KEYPAD_HASH

// Arrows
#define K_A_L HID_KEY_ARROW_LEFT
#define K_A_R HID_KEY_ARROW_RIGHT
#define K_A_U HID_KEY_ARROW_UP
#define K_A_D HID_KEY_ARROW_DOWN

// Modifiers
#define K_SHFT HID_KEY_SHIFT_RIGHT
#define K_CTRL HID_KEY_CONTROL_RIGHT
#define K_ALT  HID_KEY_ALT_RIGHT

#define MOD_CTRL 0b00000001
#define MOD_SHFT 0b00000010
#define MOD_ALT  0b00000100

#define K_ESC HID_KEY_ESCAPE

#define K_LYRUP  0xA5
#define K_LYRDWN 0xA6

// NULL
#define K_NULL  HID_KEY_NONE

#endif
