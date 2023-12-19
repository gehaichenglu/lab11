#include "sys.h"
#include "common.h"

void __am_timer_init() {
	uint32_t * time = (uint32_t*)TIME_RESET;
	time[0] = 0;
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
	uint32_t* time = (uint32_t*) TIME;
  uptime->us = time[0];
}

