#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "stdbool.h"
/**********************************************************************************
*����led�ķ���
*1.led.h �ļ����ú궨�壨������Ҫ��LED������������LED_NUMBERS������
*2.led.c �ļ������g_led[LED_NUMBERS]ȫ�ֱ�����ʼ������Ӳ���������1�ж�Ӧ�ĺ궨��
**************************************************************************************/
/******************led0 ����*********************/
#define LED_NUMBERS 1
// led0���� pc13 ����͵�ƽ��
#define LED0_RCC RCC_APB2Periph_GPIOC
#define LED0_GPIO GPIOC
#define LED0_pin GPIO_Pin_13
// �͵�ƽ����0  �ߵ�ƽ����1
#define LED0_LIGHT_MODE 0
/*************************************************/

// led�ṹ��
struct led_s {
	uint32_t rcc;
	GPIO_TypeDef *gpio;
	uint16_t pin;
	bool light_mode;
};

// numΪled����ţ���0��ʼ
int led_init(int num);
int led_init_all();
void led_on(int num);
void led_off(int num);
		 				    
#endif
