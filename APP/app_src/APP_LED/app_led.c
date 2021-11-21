#include "app_led.h"
#include "delay.h"
#include "debug.h"
#include "app_soft_timer.h"
#include "stdbool.h"

#define LED_TOGGLE_TIMER 500
struct app_led *g_app_led;

int app_led_register(struct app_led *aled)
{
	if (!aled) {
		DEBUG_PRINT_ERR("pointer* a_soft_timer is NULL");
		return -EINVAL;
	}
	g_app_led = aled;
	return 0;
}


// led 闪烁， 使用定时器时，在main函数中初始化timer3, 这里单位初始化为ms。
bool led_flag = 0;
void app_led_flash(int led_toggle_time_ms)          
{
	if (g_app_led->app_led_on && g_app_led->app_led_off) {
		if (is_soft_timeup(SOFT_TIMER0) == 0) {
			led_flag = !led_flag;
			
			if (led_flag) {
				g_app_led->app_led_on(LED0);
			} else {
				g_app_led->app_led_off(LED0);
			}
			
			set_soft_timer(SOFT_TIMER0, led_toggle_time_ms);
		}
	}
}
