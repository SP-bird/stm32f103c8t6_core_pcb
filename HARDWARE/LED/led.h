#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "stdbool.h"
/**********************************************************************************
*增加led的方法
*1.led.h 文件配置宏定义（增加需要的LED），包括配置LED_NUMBERS的数量
*2.led.c 文件中添加g_led[LED_NUMBERS]全局变量初始化，添加参数即步骤1中对应的宏定义
**************************************************************************************/
/******************led0 配置*********************/
#define LED_NUMBERS 1
// led0配置 pc13 输出低电平亮
#define LED0_RCC RCC_APB2Periph_GPIOC
#define LED0_GPIO GPIOC
#define LED0_pin GPIO_Pin_13
// 低电平亮：0  高电平亮：1
#define LED0_LIGHT_MODE 0
/*************************************************/

// led结构体
struct led_s {
	uint32_t rcc;
	GPIO_TypeDef *gpio;
	uint16_t pin;
	bool light_mode;
};

// num为led的序号，从0开始
int led_init(int num);
int led_init_all();
void led_on(int num);
void led_off(int num);
		 				    
#endif
