#include "amdev.h"
char scantokey [256] = {

	[0x76] = AM_KEY_ESCAPE,
	[0x05] = AM_KEY_F1,
	[0x06] = AM_KEY_F2,
  [0x04] = AM_KEY_F3,	
  [0x0c] = AM_KEY_F4,
	[0x03] = AM_KEY_F5,
  [0x0b] = AM_KEY_F6,
	[0x83] = AM_KEY_F7,
	[0x0a] = AM_KEY_F8,
  [0x01] = AM_KEY_F9,
  [0x09] = AM_KEY_F10,
  [0x78] = AM_KEY_F11,
  [0x07] = AM_KEY_F12,
	[0x0e] = AM_KEY_GRAVE,
	[0x16] = AM_KEY_1,
	[0x1e] = AM_KEY_2,
	[0x26] = AM_KEY_3,
	[0x25] = AM_KEY_4,
	[0x2e] = AM_KEY_5,
	[0x36] = AM_KEY_6,
	[0x3d] = AM_KEY_7,
	[0x3e] = AM_KEY_8,
	[0x46] = AM_KEY_9,
	[0x45] = AM_KEY_0,
	[0x4e] = AM_KEY_MINUS,
	[0x55] = AM_KEY_EQUALS,
	[0x66] = AM_KEY_BACKSPACE,
	[0x0d] = AM_KEY_TAB,
	[0x15] = AM_KEY_Q,
	[0x1d] = AM_KEY_W,
	[0x24] = AM_KEY_E,
	[0x2d] = AM_KEY_R,
  [0x2c] = AM_KEY_T,
  [0x35] = AM_KEY_Y,
  [0x3c] = AM_KEY_U,
	[0x43] = AM_KEY_I,
  [0x44] = AM_KEY_O,
  [0x4d] = AM_KEY_P,
  [0x54] = AM_KEY_LEFTBRACKET,
	[0x5b] = AM_KEY_RIGHTBRACKET,
  [0x5d] = AM_KEY_BACKSLASH,
  [0x58] = AM_KEY_CAPSLOCK,
  [0x1c] = AM_KEY_A,
	[0x1b] = AM_KEY_S,
  [0x23] = AM_KEY_D,
  [0x2b] = AM_KEY_F,
  [0x34] = AM_KEY_G,
	[0x33] = AM_KEY_H,         
  [0x3b] = AM_KEY_J,         
  [0x42] = AM_KEY_K,
  [0x4b] = AM_KEY_L,
	[0x4c] = AM_KEY_SEMICOLON,
  [0x52] = AM_KEY_APOSTROPHE,
  [0x5a] = AM_KEY_RETURN,
  [0x12] = AM_KEY_LSHIFT,
	[0x1a] = AM_KEY_Z,
  [0x22] = AM_KEY_X,
  [0x21] = AM_KEY_C,
  [0x2a] = AM_KEY_V,
	[0x32] = AM_KEY_B,         
  [0x31] = AM_KEY_N,         
  [0x3a] = AM_KEY_M,
  [0x41] = AM_KEY_COMMA,
	[0x49] = AM_KEY_PERIOD,
  [0x4a] = AM_KEY_SLASH,
  [0x59] = AM_KEY_RSHIFT,
  [0x14] = AM_KEY_LCTRL,
  [0x11] = AM_KEY_LALT,
  [0x29] = AM_KEY_SPACE,
  //[0x75] = AM_KEY_UP,
  //[0x72] = AM_KEY_DOWN,
  //[0x6b] = AM_KEY_LEFT,
	//[0x74] = AM_KEY_RIGHT,
  //[0x70] = AM_KEY_INSERT,
  //[0x71] = AM_KEY_DELETE,
  //[0x6c] = AM_KEY_HOME,
	//[0x69] = AM_KEY_END,
  //[0x7d] = AM_KEY_PAGEUP,
  //[0x7a] = AM_KEY_PAGEDOWN,
	[0x70] = AM_KEY_RIGHT_0,
	[0x69] = AM_KEY_RIGHT_1,
	[0x72] = AM_KEY_RIGHT_2,
	[0x7a] = AM_KEY_RIGHT_3,
	[0x6b] = AM_KEY_RIGHT_4,
	[0x73] = AM_KEY_RIGHT_5,
	[0x74] = AM_KEY_RIGHT_6,
	[0x6c] = AM_KEY_RIGHT_7,
	[0x75] = AM_KEY_RIGHT_8,
	[0x7d] = AM_KEY_RIGHT_9,
	[0x7b] = AM_KEY_RIGHT_MINUS,
	[0x79] = AM_KEY_RIGHT_PLUS,
	[0x7c] = AM_KEY_RIGHT_MULTI,
	[0x71] = AM_KEY_RIGHT_PERIOD,
};
char keytoascii [128] = {
	[AM_KEY_NONE] = 0,
	[AM_KEY_ESCAPE] = 0,
	[AM_KEY_F1] = 0,
	[AM_KEY_F2] = 0,
  [AM_KEY_F3] = 0,
  [AM_KEY_F4] = 0,
	[AM_KEY_F5] = 0,
  [AM_KEY_F6] = 0,
	[AM_KEY_F7] = 0,
	[AM_KEY_F8] = 0,
  [AM_KEY_F9] = 0,
  [AM_KEY_F10] = 0,
  [AM_KEY_F11] = 0,
  [AM_KEY_F12] = 0,
	[AM_KEY_GRAVE] = '`',
	[AM_KEY_1] = '1',
	[AM_KEY_2] = '2',
	[AM_KEY_3] = '3',
	[AM_KEY_4] = '4',
	[AM_KEY_5] = '5',
	[AM_KEY_6] = '6',
	[AM_KEY_7] = '7',
	[AM_KEY_8] = '8',
	[AM_KEY_9] = '9',
	[AM_KEY_0] = '0',
	[AM_KEY_MINUS] = '-',
	[AM_KEY_EQUALS] = '=',
	[AM_KEY_BACKSPACE] = 0x08,
	[AM_KEY_TAB] = 0x09,
	[AM_KEY_Q] = 'q',
	[AM_KEY_W] = 'w',
	[AM_KEY_E] = 'e',
	[AM_KEY_R] = 'r',
  [AM_KEY_T] = 't',
  [AM_KEY_Y] = 'y',
  [AM_KEY_U] = 'u',
	[AM_KEY_I] = 'i',
  [AM_KEY_O] = 'o',
  [AM_KEY_P] = 'p',
  [AM_KEY_LEFTBRACKET] = '[',
	[AM_KEY_RIGHTBRACKET] = ']',
  [AM_KEY_BACKSLASH] = 0x5c,
  [AM_KEY_CAPSLOCK] = 0,
  [AM_KEY_A] = 'a',
	[AM_KEY_S] = 's',
  [AM_KEY_D] = 'd',
  [AM_KEY_F] = 'f',
  [AM_KEY_G] = 'g',
	[AM_KEY_H] = 'h', 
  [AM_KEY_J] = 'j',
  [AM_KEY_K] = 'k',
  [AM_KEY_L] = 'l',
	[AM_KEY_SEMICOLON] = ';',
  [AM_KEY_APOSTROPHE] = 0x27,
  [AM_KEY_RETURN] = 0x0d,
  [AM_KEY_LSHIFT] = 0,
	[AM_KEY_Z] = 'z',
  [AM_KEY_X] = 'x',
  [AM_KEY_C] = 'c',
  [AM_KEY_V] = 'v',
	[AM_KEY_B] = 'b',      
  [AM_KEY_N] = 'n',
  [AM_KEY_M] = 'm',
  [AM_KEY_COMMA] = ',',
	[AM_KEY_PERIOD] = '.',
  [AM_KEY_SLASH] = '/',
  [AM_KEY_RSHIFT] = 0,
  [AM_KEY_LCTRL] = 0,
  [AM_KEY_LALT] = 0,
  [AM_KEY_SPACE] = ' ',
  [AM_KEY_UP] = 0,
  [AM_KEY_DOWN] = 0,
  [AM_KEY_LEFT] = 0,
	[AM_KEY_RIGHT] = 0,
  [AM_KEY_INSERT] = 0,
  [AM_KEY_DELETE] = 0,
  [AM_KEY_HOME] = 0,
	[AM_KEY_END] = 0,
  [AM_KEY_PAGEUP] = 0,
  [AM_KEY_PAGEDOWN] = 0,
	[AM_KEY_RIGHT_0] = '0',
	[AM_KEY_RIGHT_1] = '1',
	[AM_KEY_RIGHT_2] = '2',
	[AM_KEY_RIGHT_3] = '3',
	[AM_KEY_RIGHT_4] = '4',
	[AM_KEY_RIGHT_5] = '5',
	[AM_KEY_RIGHT_6] = '6',
	[AM_KEY_RIGHT_7] = '7',
	[AM_KEY_RIGHT_8] = '8',
	[AM_KEY_RIGHT_9] = '9',
	[AM_KEY_RIGHT_MINUS] = '-',
	[AM_KEY_RIGHT_PLUS] = '+',
	[AM_KEY_RIGHT_MULTI] = '*',
	[AM_KEY_RIGHT_PERIOD] = '.',
};
char keytocapascii [128] = {
	[AM_KEY_NONE] = 0,
	[AM_KEY_ESCAPE] = 0,
	[AM_KEY_F1] = 0,
	[AM_KEY_F2] = 0,
  [AM_KEY_F3] = 0,
  [AM_KEY_F4] = 0,
	[AM_KEY_F5] = 0,
  [AM_KEY_F6] = 0,
	[AM_KEY_F7] = 0,
	[AM_KEY_F8] = 0,
  [AM_KEY_F9] = 0,
  [AM_KEY_F10] = 0,
  [AM_KEY_F11] = 0,
  [AM_KEY_F12] = 0,
	[AM_KEY_GRAVE] = '~',
	[AM_KEY_1] = '!',
	[AM_KEY_2] = '@',
	[AM_KEY_3] = '#',
	[AM_KEY_4] = '$',
	[AM_KEY_5] = '%',
	[AM_KEY_6] = '^',
	[AM_KEY_7] = '&',
	[AM_KEY_8] = '*',
	[AM_KEY_9] = '(',
	[AM_KEY_0] = ')',
	[AM_KEY_MINUS] = '_',
	[AM_KEY_EQUALS] = '+',
	[AM_KEY_BACKSPACE] = 0x08,
	[AM_KEY_TAB] = 0x09,
	[AM_KEY_Q] = 'Q',
	[AM_KEY_W] = 'W',
	[AM_KEY_E] = 'E',
	[AM_KEY_R] = 'R',
  [AM_KEY_T] = 'T',
  [AM_KEY_Y] = 'Y',
  [AM_KEY_U] = 'U',
	[AM_KEY_I] = 'I',
  [AM_KEY_O] = 'O',
  [AM_KEY_P] = 'P',
  [AM_KEY_LEFTBRACKET] = '{',
	[AM_KEY_RIGHTBRACKET] = '}',
  [AM_KEY_BACKSLASH] = 0x5c,
  [AM_KEY_CAPSLOCK] = 0,
  [AM_KEY_A] = 'A',
	[AM_KEY_S] = 'S',
  [AM_KEY_D] = 'D',
  [AM_KEY_F] = 'F',
  [AM_KEY_G] = 'G',
	[AM_KEY_H] = 'H', 
  [AM_KEY_J] = 'J',
  [AM_KEY_K] = 'K',
  [AM_KEY_L] = 'L',
	[AM_KEY_SEMICOLON] = ':',
  [AM_KEY_APOSTROPHE] = 0x22,
  [AM_KEY_RETURN] = 0x0d,
  [AM_KEY_LSHIFT] = 0,
	[AM_KEY_Z] = 'Z',
  [AM_KEY_X] = 'X',
  [AM_KEY_C] = 'C',
  [AM_KEY_V] = 'V',
	[AM_KEY_B] = 'B',      
  [AM_KEY_N] = 'N',
  [AM_KEY_M] = 'M',
  [AM_KEY_COMMA] = '<',
	[AM_KEY_PERIOD] = '>',
  [AM_KEY_SLASH] = '?',
  [AM_KEY_RSHIFT] = 0,
  [AM_KEY_LCTRL] = 0,
  [AM_KEY_LALT] = 0,
  [AM_KEY_SPACE] = ' ',
  [AM_KEY_UP] = 0,
  [AM_KEY_DOWN] = 0,
  [AM_KEY_LEFT] = 0,
	[AM_KEY_RIGHT] = 0,
  [AM_KEY_INSERT] = 0,
  [AM_KEY_DELETE] = 0,
  [AM_KEY_HOME] = 0,
	[AM_KEY_END] = 0,
  [AM_KEY_PAGEUP] = 0,
  [AM_KEY_PAGEDOWN] = 0,
	[AM_KEY_RIGHT_0] = '0',
	[AM_KEY_RIGHT_1] = '1',
	[AM_KEY_RIGHT_2] = '2',
	[AM_KEY_RIGHT_3] = '3',
	[AM_KEY_RIGHT_4] = '4',
	[AM_KEY_RIGHT_5] = '5',
	[AM_KEY_RIGHT_6] = '6',
	[AM_KEY_RIGHT_7] = '7',
	[AM_KEY_RIGHT_8] = '8',
	[AM_KEY_RIGHT_9] = '9',
	[AM_KEY_RIGHT_MINUS] = '-',
	[AM_KEY_RIGHT_PLUS] = '+',
	[AM_KEY_RIGHT_MULTI] = '*',
	[AM_KEY_RIGHT_PERIOD] = '.',
};
