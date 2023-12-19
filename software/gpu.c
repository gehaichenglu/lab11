#include "sys.h"

#include "common.h"
#include "am.h"
#include "amdev.h"
#include "klib.h"
#include "klib-macros.h"

void __am_gpu_init(){
	uint32_t* vgactrl = (uint32_t*) VGA_CONTROL;
	vgactrl[0] = 0;
	uint32_t *fb = (uint32_t*) (uintptr_t) VGA_MEM;
	int w = VGA_WIDTH;
	int h = VGA_DEPTH;
	int ww = 0;
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			fb[ww + j] = 0;
		}
		ww += w;
	}
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
	uint32_t *fb = (uint32_t*)(uintptr_t)VGA_MEM;
	int w = VGA_WIDTH;
	int h = VGA_DEPTH;
	int idx = 0;
	int ww = __mulsi3(ctl->y, w);
	for(int i = ctl->y;  i < ctl->y + ctl->h; i ++){
		for(int j = ctl->x;  j < ctl->x + ctl->w; j ++){
			fb[ ww + j] = ((uint32_t*)ctl->pixels)[idx++];
		}
		ww += w;
	}
}

void __am_gpu_control(AM_GPU_CONTROL_T* ctl){
	uint32_t* vgactrl = (uint32_t*) VGA_CONTROL;
	vgactrl[0] = ctl->ctrl;
}
