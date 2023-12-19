#ifndef __AMDEV_H__            
#define __AMDEV_H__


#include "common.h"
#include <stdarg.h>

#define AM_DEVREG(id, reg, perm, ...) \
  enum { AM_##reg = (id) }; \
  typedef struct { __VA_ARGS__; } AM_##reg##_T;

AM_DEVREG( 1, TIMER_UPTIME, RD, uint32_t us);
AM_DEVREG( 2, INPUT_KEYBRD, RD, bool keydown; int keycode);
AM_DEVREG( 3, GPU_FBDRAW,   WR, int x, y; void *pixels; int w, h; bool sync);
AM_DEVREG( 4, GPU_CONTROL,  WR, int ctrl);

#define AM_KEYS(_) \
  _(ESCAPE) _(F1) _(F2) _(F3) _(F4) _(F5) _(F6) _(F7) _(F8) _(F9) _(F10) _(F11) _(F12) \
  _(GRAVE) _(1) _(2) _(3) _(4) _(5) _(6) _(7) _(8) _(9) _(0) _(MINUS) _(EQUALS) _(BACKSPACE) \
  _(TAB) _(Q) _(W) _(E) _(R) _(T) _(Y) _(U) _(I) _(O) _(P) _(LEFTBRACKET) _(RIGHTBRACKET) _(BACKSLASH) \
  _(CAPSLOCK) _(A) _(S) _(D) _(F) _(G) _(H) _(J) _(K) _(L) _(SEMICOLON) _(APOSTROPHE) _(RETURN) \
  _(LSHIFT) _(Z) _(X) _(C) _(V) _(B) _(N) _(M) _(COMMA) _(PERIOD) _(SLASH) _(RSHIFT) \
  _(LCTRL) _(APPLICATION) _(LALT) _(SPACE) _(RALT) _(RCTRL) \
  _(UP) _(DOWN) _(LEFT) _(RIGHT) _(INSERT) _(DELETE) _(HOME) _(END) _(PAGEUP) _(PAGEDOWN)

#define AM_KEYS_RIGHT(_) \
	_(1) _(2) _(0) _(3) _(4) _(5) _(6) _(7) _(8) _(9) _(PERIOD) _(PLUS) _(MINUS) _(MULTI) 

#define AM_KEY_NAMES(key) AM_KEY_##key,
#define AM_KEY_RIGHT_NAMES(key) AM_KEY_RIGHT_##key,

enum {
  AM_KEY_NONE = 0,
  AM_KEYS(AM_KEY_NAMES)
	AM_KEYS_RIGHT(AM_KEY_RIGHT_NAMES)
};

#endif
