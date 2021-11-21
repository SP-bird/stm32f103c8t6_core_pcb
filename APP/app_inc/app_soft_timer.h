#ifndef __SOFT_TIMER_H
#define __SOFT_TIMER_H
#include "sys.h"
#include "stdbool.h"

// 暂时只有3个，数量取决于timer3.c 中定义的数量
#define SOFT_TIMER0 0
#define SOFT_TIMER1 1
#define SOFT_TIMER2 2

struct soft_timer {
	int soft_timer_numbers;
	void (*set_soft_timer)(int soft_timer_x, u32 t);
	bool (*is_timeup)(int soft_timer_x);
};

int app_soft_timer_register(struct soft_timer *a_soft_timer);
int set_soft_timer(int soft_timer_x, u32 t);
// 返回值为1，则表示时间还没到；小于0表示，发生错误；等于0，表示时间到
int is_soft_timeup(int soft_timer_x);

#endif
