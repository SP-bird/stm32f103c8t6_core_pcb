#ifndef __KEY_H_
#define __KEY_H_
#include "sys.h"
#include "stdbool.h"
/**********************************************************************************
*增加key的方法
*1.key.h 文件配置宏定义（增加需要的KEY），包括配置KEY_NUMBERS的数量
*2.key.c 文件中添加g_key[KEY_NUMBERS]全局变量初始化，添加参数即步骤1中对应的宏定义
**************************************************************************************/
#define KEY_NUMBERS 1
/******************led0 配置*********************/
#define KEY0 0
// key0配置 pb3 检测到低电平表示按键按下
#define KEY0_RCC RCC_APB2Periph_GPIOB
#define KEY0_GPIO GPIOB
#define KEY0_pin GPIO_Pin_5
// 低电平亮：0  高电平亮：1
#define KEY0_DECTECT_MODE 0

#define KEY0_GPIO_PortSource		GPIO_PortSourceGPIOB
#define KEY0_GPIO_PinSource		GPIO_PinSource5
#define KEY0_EXTI_LINE 		EXTI_Line5
#define KEY0_EXTIx_IRQn   EXTI15_10_IRQn
/*************************************************/


// key结构体
struct key_s {
	uint32_t rcc;
	GPIO_TypeDef *gpio;
	uint16_t pin;
	uint8_t gpio_portsource;
	uint8_t gpio_pinsource;
	uint32_t exit_line;
	uint8_t nvic_irq_channel;
	bool detect_mode;
};

int key_scan();
int key_init_all();
#endif



