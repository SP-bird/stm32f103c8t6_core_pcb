#include "timer4.h"
   	  
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM4_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM4�ж�,��������ж�

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx����
							 
}
//��ʱ��4�жϷ������
void TIM4_IRQHandler(void)   //TIM4�ж�
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		}
}




//TIM4 CH1 PWM �������
//PWM �����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
/*
STM32F103C8T6
PB6 - TIM4_CH1
PB7 - TIM4_CH2
PB8 - TIM4_CH3
PB9 - TIM4_CH4
*/
void TIM4_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ�� TIMx ����
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ�� PB ʱ��
	TIM_DeInit(TIM4);
 
  //���ø�����Ϊ�����������,��� TIM4 CH1 �� PWM ���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; //TIM4_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //���ù������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ�� GPIO
 
	TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����Ԥ��Ƶֵ ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //��ʼ�� TIMx
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //CH1 PWM2 ģʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	
	
	TIM_OCInitStructure.TIM_Pulse = 200; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 �ߵ�ƽ��Ч
	TIM_OC1Init(TIM4, &TIM_OCInitStructure); //����ָ���Ĳ�����ʼ������ TIMx
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH1 Ԥװ��ʹ��
	
	
	TIM_OCInitStructure.TIM_Pulse = 400; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC2 �ߵ�ƽ��Ч
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); //����ָ���Ĳ�����ʼ������ TIMx
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH2 Ԥװ��ʹ��
	
	
	TIM_OCInitStructure.TIM_Pulse = 600; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 �ߵ�ƽ��Ч
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); //����ָ���Ĳ�����ʼ������ TIMx
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH3 Ԥװ��ʹ��
	
	
	TIM_OCInitStructure.TIM_Pulse = 800; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 �ߵ�ƽ��Ч
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); //����ָ���Ĳ�����ʼ������ TIMx
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH4 Ԥװ��ʹ��
	
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ�� TIMx �� ARR �ϵ�Ԥװ�ؼĴ���
//	TIM_CtrlPWMOutputs(TIM4,ENABLE);  //MOE �����ʹ��,�߼���ʱ�����뿪��
	TIM_Cmd(TIM4, ENABLE); //ʹ�� TIMx
}


/**
TIM_SetCompare1(TIM4,500);
TIM_SetCompare2(TIM4,500);
TIM_SetCompare3(TIM4,500);
TIM_SetCompare4(TIM4,500);
���ø���ͨ����ռ�ձȣ�ռ�ձ�Ϊ��500/arr��main������arr����Ϊ899,��ռ�ձ�Ϊ500/899
**/