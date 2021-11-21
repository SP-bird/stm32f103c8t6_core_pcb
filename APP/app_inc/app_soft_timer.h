#ifndef __SOFT_TIMER_H
#define __SOFT_TIMER_H
#include "sys.h"
#include "stdbool.h"

// ��ʱֻ��3��������ȡ����timer3.c �ж��������
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
// ����ֵΪ1�����ʾʱ�仹û����С��0��ʾ���������󣻵���0����ʾʱ�䵽
int is_soft_timeup(int soft_timer_x);

#endif
