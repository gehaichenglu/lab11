#include "klib.h"
#include "am.h"
#include "klib-macros.h"
#include "common.h"
#include "sys.h"
#include "amdev.h"

#define FPS 30
#define N   32

static inline uint32_t pixel(uint8_t r, uint8_t g, uint8_t b) {
  return (r << 16) | (g << 8) | b;
}
static inline uint8_t R(uint32_t p) { return p >> 16; }
static inline uint8_t G(uint32_t p) { return p >> 8; }
static inline uint8_t B(uint32_t p) { return p; }

static uint32_t canvas[N][N];
static int used[N][N];

static uint32_t color_buf[32 * 32];

void redraw() {
  int w = __udivsi3( 640, N);
  int h = __udivsi3( 480, N);
  int block_size = __mulsi3(w , h);
  //assert((uint32_t)block_size <= LENGTH(color_buf));

  int x, y, k;
  for (y = 0; y < N; y ++) {
    for (x = 0; x < N; x ++) {
      for (k = 0; k < block_size; k ++) {
				uint32_t* can = (uint32_t*) canvas;
        //color_buf[k] = canvas[y][x];
				color_buf[k] = can[__mulsi3(N, y) + x];
      }
      io_write(AM_GPU_FBDRAW,__mulsi3( x , w),__mulsi3( y , h), color_buf, w, h, false);
    }
  }
  //io_write(AM_GPU_FBDRAW, 0, 0, NULL, 0, 0, true);
}

static uint32_t p(int tsc) {
  int b = tsc & 0xff;
  return pixel(__mulsi3(b , 6),__mulsi3( b , 7), b);
}

void update() {
  static int tsc = 0;
  static int dx[4] = {0, 1, 0, -1};
  static int dy[4] = {1, 0, -1, 0};

  tsc ++;

			int* us = (int*)used;
			uint32_t* can = (uint32_t*) canvas;
  for (int i = 0; i < N; i ++)
    for (int j = 0; j < N; j ++) {
      //used[i][j] = 0;
			us[__mulsi3(i, N) + j] = 0;
    }

  int init = tsc;
  //canvas[0][0] = p(init); used[0][0] = 1;
	can[0] = p(init); us[0] = 1;
  int x = 0, y = 0, d = 0;
  for (int step = 1; step < 1024; step ++) {
    for (int t = 0; t < 4; t ++) {
      int x1 = x + dx[d], y1 = y + dy[d];
      if (x1 >= 0 && x1 < N && y1 >= 0 && y1 < N && !us[__mulsi3(x1, N) + y1]) {
        x = x1; y = y1;
				us[__mulsi3(x, N) + y] = 1;
        //used[x][y] = 1;
        //canvas[x][y] = p(init + step / 2);
				can[__mulsi3(x, N) + y] = p(init + (step >> 1));
        break;
      }
      d = __umodsi3((d + 1) , 4);
    }
  }
}

void video_test() {
	ioe_init();
  unsigned long last = 0;
  unsigned long fps_last = 0;
  int fps = 0;
AM_GPU_CONTROL_T ctrl;
ctrl.ctrl = 1;
ioe_write(AM_GPU_CONTROL, &ctrl);
  while (1) {

			AM_INPUT_KEYBRD_T ev;// = io_read(AM_INPUT_KEYBRD);
      ioe_read(AM_INPUT_KEYBRD, &ev); 
      if (ev.keydown && ev.keycode == AM_KEY_ESCAPE){
        ctrl.ctrl = 0;         
        ioe_write(AM_GPU_CONTROL, &ctrl);
        return;                
      }

		AM_TIMER_UPTIME_T us;
		ioe_read(AM_TIMER_UPTIME, &us);
    unsigned long upt = __udivsi3(us.us , 1000);
    if (upt - last > __udivsi3(1000 , FPS)) {
      update();
      redraw();
      last = upt;
      fps ++;
    }
    if (upt - fps_last > 1000) {
      // display fps every 1s
      //printf("%d: FPS = %d\n", upt, fps);
      fps_last = upt;
      fps = 0;
    }
  }
}
