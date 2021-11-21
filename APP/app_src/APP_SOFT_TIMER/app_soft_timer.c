#include "app_soft_timer.h"
#include "debug.h"

struct soft_timer *g_app_soft_timer;

int app_soft_timer_register(struct soft_timer *a_soft_timer)
{
	if (!a_soft_timer) {
			DEBUG_PRINT_ERR("pointer* a_soft_timer is NULL");
			return -EINVAL;
	}
	g_app_soft_timer = a_soft_timer;
	
	return 0;
}

int set_soft_timer(int soft_timer_x, u32 t)
{
	if ((soft_timer_x < 0) || (soft_timer_x >= g_app_soft_timer->soft_timer_numbers) ) {
		DEBUG_PRINT_ERR("soft_timer_x %d number is error, soft_timer_x should be not smaller than 0 or lager than %d\r\n", soft_timer_x, g_app_soft_timer->soft_timer_numbers);
		return -EINVAL;
	}
	
	if (g_app_soft_timer->set_soft_timer) {
		g_app_soft_timer->set_soft_timer(soft_timer_x, t);
	}
	
	return 0;
}

// 返回值为1，则表示时间还没到；小于0表示，发生错误；等于0，表示时间到
int is_soft_timeup(int soft_timer_x)
{
	if ((soft_timer_x < 0) || (soft_timer_x >= g_app_soft_timer->soft_timer_numbers) ) {
		DEBUG_PRINT_ERR("soft_timer_x %d number is error, soft_timer_x should be not smaller than 0 or lager than %d\r\n", soft_timer_x, g_app_soft_timer->soft_timer_numbers);
		return -EINVAL;
	}
	
	if (g_app_soft_timer->is_timeup) {
		if (g_app_soft_timer->is_timeup(soft_timer_x))
		{
			return 0;
		} else {
			return 1;
		}
	}
	DEBUG_PRINT_ERR("pointer* a_soft_timer is NULL");
	return -EINVAL;
}
