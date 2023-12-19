#include "am.h"
#include "amdev.h"
#include "common.h"
#include "klib-macros.h"

void __am_timer_init();
void __am_gpu_init();
void __am_input_keybrd(AM_INPUT_KEYBRD_T *);
void __am_timer_uptime(AM_TIMER_UPTIME_T *);
void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *);
void __am_gpu_control(AM_GPU_CONTROL_T *);

typedef void (*handler_t)(void *buf);
static handler_t lut[12] = {
  [AM_TIMER_UPTIME] = __am_timer_uptime,
  [AM_INPUT_KEYBRD] = __am_input_keybrd,
  [AM_GPU_FBDRAW  ] = __am_gpu_fbdraw,
  [AM_GPU_CONTROL  ] = __am_gpu_control,
};


bool ioe_init() {
  __am_gpu_init();
  __am_timer_init();
  return true;
}

void ioe_read (int reg, void *buf) { ((handler_t)lut[reg])(buf); }
void ioe_write(int reg, void *buf) { ((handler_t)lut[reg])(buf); }
