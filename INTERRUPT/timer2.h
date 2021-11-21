#ifndef __TIMER2_H
#define __TIMER2_H
#include "sys.h"

int get_uptime_num(int num);
void clear_uptime_num(int num);
void TIM2_Int_Init(u16 arr,u16 psc);
#endif
