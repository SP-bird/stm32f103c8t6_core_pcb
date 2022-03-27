#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "debug.h"
#include "config.h"
#include "app_led.h"
#include "timer3.h"
#include "timer4.h"
#include "timer2.h"
#include "key.h" 
#include "app_oled.h"
#include "app_wifi.h"

 int main(void)
 {	
	int ret;
	u8 key_value = 0;
	int led_toggle_time_ms = 250;
	int led_toggle_mode = 0;
	 
	delay_init();	    //延时函数初始化
	uart_init(115200);
	TIM2_Int_Init(10,7199);
//	TIM4_PWM_Init(899,0);	 //不分频。PWM频率=72000000/900=80Khz
#if PWM_CONFIG
	TIM3_PWM_Init(899,0);	 //不分频。PWM频率=72000000/900=80Khz
#endif
	 
#if TIMER3_SOFT_CONFIG
	 soft_timer_init(10,7199); // 定时1ms,  1kHz = 72M / (7199 + 1) / 10
#endif
	 
#if LED_CONFIG
	ret = led_init_all();
	if (ret != 0) {
		DEBUG_PRINT_ERR("led initialize failed , ret = 0x%x\r\n", ret);
	}
#endif
	
	KEY_Init();
	
#if OLED_CONFIG
	OLED_Init();			//初始化OLED  
	app_oled_test();
#endif
//	TIM_SetCompare3(TIM4,500);

#if WIFI_CONFIG
	app_wifi_init();
#endif
	
	while(1)
	{
		key_value = KEY_Scan(0);
		if (key_value == KEY0_PRES) {
			led_toggle_mode++;
			led_toggle_mode = led_toggle_mode % 9;
			led_toggle_time_ms = 250 * led_toggle_mode;	
		#if OLED_CONFIG
			app_oled_test1(led_toggle_mode);
		#endif
		}

		app_led_flash(led_toggle_time_ms);
		
	#if OLED_CONFIG
//		app_oled_test();
	#endif
		
	#if WIFI_CONFIG
		app_wifi_test();
	#endif
	
	}
 }

