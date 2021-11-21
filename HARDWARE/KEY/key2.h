#ifndef __KEY_H_
#define __KEY_H_
#include "sys.h"
#include "stdbool.h"
/**********************************************************************************
*����key�ķ���
*1.key.h �ļ����ú궨�壨������Ҫ��KEY������������KEY_NUMBERS������
*2.key.c �ļ������g_key[KEY_NUMBERS]ȫ�ֱ�����ʼ������Ӳ���������1�ж�Ӧ�ĺ궨��
**************************************************************************************/
#define KEY_NUMBERS 1
/******************led0 ����*********************/
#define KEY0 0
// key0���� pb3 ��⵽�͵�ƽ��ʾ��������
#define KEY0_RCC RCC_APB2Periph_GPIOB
#define KEY0_GPIO GPIOB
#define KEY0_pin GPIO_Pin_5
// �͵�ƽ����0  �ߵ�ƽ����1
#define KEY0_DECTECT_MODE 0

#define KEY0_GPIO_PortSource		GPIO_PortSourceGPIOB
#define KEY0_GPIO_PinSource		GPIO_PinSource5
#define KEY0_EXTI_LINE 		EXTI_Line5
#define KEY0_EXTIx_IRQn   EXTI15_10_IRQn
/*************************************************/


// key�ṹ��
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



