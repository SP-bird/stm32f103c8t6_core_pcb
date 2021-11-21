#include "led.h"
#include "debug.h"
#include "app_led.h"
// led结构体数组初始化赋值
//struct led_s g_led[LED_NUMBERS] = {
//	{LED0_RCC, LED0_GPIO, LED0_pin, LED0_LIGHT_MODE}
//};

struct led_s g_led[LED_NUMBERS] = {
	{
		.rcc = LED0_RCC,
		.gpio = LED0_GPIO,
		.pin = LED0_pin,
		.light_mode = LED0_LIGHT_MODE
	}
};

// num: led灯的序号
int led_init(int num)
{
	if((num < 0) || (num >= LED_NUMBERS)) {
		DEBUG_PRINT_ERR("led%d initialize failed , led number is 0 ~ %d\r\n", num, LED_NUMBERS - 1);
		return -EINVAL;
	}
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(g_led[num].rcc, ENABLE);	 //使能PB,PE端口时钟
		
	GPIO_InitStructure.GPIO_Pin = g_led[num].pin;				 //LED0-->PB.5 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(g_led[num].gpio, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	
	return 0;
}



void led_on(int num)
{
	(g_led[num].light_mode == g_led[num].light_mode) ? GPIO_ResetBits(g_led[num].gpio, g_led[num].pin) : GPIO_SetBits(g_led[num].gpio, g_led[num].pin);
}

void led_off(int num)
{
	(g_led[num].light_mode == !g_led[num].light_mode) ? GPIO_ResetBits(g_led[num].gpio, g_led[num].pin) : GPIO_SetBits(g_led[num].gpio, g_led[num].pin);
}

struct app_led g_led_op = {
	.numbers = LED_NUMBERS,
	.app_led_on = led_on,
	.app_led_off = led_off
};

int led_init_all()
{
	int ret;
	int i;
	for (i = 0; i < LED_NUMBERS; i++) {
		ret = led_init(i);
		if (ret != 0) {
			DEBUG_PRINT_ERR("led%d initialize failed, ret = 0x%x\r\n", ret, i);
			return ret;
		}
	}
	
	ret = app_led_register(&g_led_op); // 向app_led注册led驱动函数
	if (ret != 0) {
		DEBUG_PRINT_ERR("led register failed, ret = 0x%x", ret);
		return ret;
	}
	
	return 0;
}