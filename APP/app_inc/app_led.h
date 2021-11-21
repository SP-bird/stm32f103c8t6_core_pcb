#ifndef __APP_LED_H
#define __APP_LED_H

// 具体led数量取决于led.c中定义
#define LED0 0
#define LED1 1
#define LED2 2

struct app_led {
	int numbers; 
	void (*app_led_on)(int num);
	void (*app_led_off)(int num);
};

int app_led_register(struct app_led *aled);
void app_led_flash(int led_toggle_time_ms);
#endif
