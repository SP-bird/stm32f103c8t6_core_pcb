#include "key2.h"
#include "timer2.h"
#include "debug.h"

int myKey_IsPressed_Flag[KEY_NUMBERS];
// ����key����
struct key_s g_key[KEY_NUMBERS] = {
	{
		.rcc = KEY0_RCC,
		.gpio = KEY0_GPIO,
		.pin = KEY0_pin,
		.gpio_portsource = KEY0_GPIO_PortSource,
		.gpio_pinsource = KEY0_GPIO_PinSource,
		.exit_line = KEY0_EXTI_LINE,
		.nvic_irq_channel = KEY0_EXTIx_IRQn,
		.detect_mode = KEY0_DECTECT_MODE
	}
};

// num: key�����
int key_init(int num)
{
	if((num < 0) || (num >= KEY_NUMBERS)) {
		DEBUG_PRINT_ERR("key%d initialize failed , key number is 0 ~ %d\r\n", num, KEY_NUMBERS - 1);
		return -EINVAL;
	}
	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(g_key[num].rcc, ENABLE);	 //ʹ�ܶ˿�ʱ��
		
	GPIO_InitStructure.GPIO_Pin = g_key[num].pin;				 //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(g_key[num].gpio, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOX
	
	/* ��ʼ��EXTI���� */
	/* ѡ����ΪEXTI�ߵ�GPIO���� */
	GPIO_EXTILineConfig( g_key[num].gpio_portsource , g_key[num].gpio_pinsource);
	/* �����ж�or�¼��� */
	EXTI_InitStruct.EXTI_Line = g_key[num].exit_line;
	/* ����ģʽ���ж�or�¼� */
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/* ���ñ��ش��� ����or�½� */
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	/* ʹ��EXTI�� */
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStructure.NVIC_IRQChannel = g_key[num].nvic_irq_channel;  //
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	
	return 0;
}


void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(g_key[KEY0].exit_line)!=RESET)
	{
	clear_uptime_num(KEY0);
	while(get_uptime_num(KEY0) > 10);
	if(!GPIO_ReadInputDataBit(g_key[KEY0].gpio, g_key[KEY0].pin))
	{
		myKey_IsPressed_Flag[KEY0] = 1;
	}
	
	EXTI_ClearITPendingBit(g_key[KEY0].exit_line);
	}
}

int key_init_all()
{
	int ret;
	int i;
	for (i = 0; i < KEY_NUMBERS; i++) {
		ret = key_init(i);
		if (ret != 0) {
			DEBUG_PRINT_ERR("led%d initialize failed, ret = 0x%x\r\n", ret, i);
			return ret;
		}
	}
	
	return 0;
}

int key_scan()
{
	if (myKey_IsPressed_Flag[KEY0]) {
		myKey_IsPressed_Flag[KEY0] = 0;
		return KEY0 + 1;
	}
	return 0;
}