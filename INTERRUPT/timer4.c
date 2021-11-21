#include "timer4.h"
   	  
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM4_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM4中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM4, ENABLE);  //使能TIMx外设
							 
}
//定时器4中断服务程序
void TIM4_IRQHandler(void)   //TIM4中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		}
}




//TIM4 CH1 PWM 输出设置
//PWM 输出初始化
//arr：自动重装值
//psc：时钟预分频数
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
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //使能 TIMx 外设
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能 PB 时钟
	TIM_DeInit(TIM4);
 
  //设置该引脚为复用输出功能,输出 TIM4 CH1 的 PWM 脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; //TIM4_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用功能输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化 GPIO
 
	TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载周期值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置预分频值 不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //初始化 TIMx
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //CH1 PWM2 模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	
	
	TIM_OCInitStructure.TIM_Pulse = 200; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 高电平有效
	TIM_OC1Init(TIM4, &TIM_OCInitStructure); //根据指定的参数初始化外设 TIMx
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH1 预装载使能
	
	
	TIM_OCInitStructure.TIM_Pulse = 400; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC2 高电平有效
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); //根据指定的参数初始化外设 TIMx
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH2 预装载使能
	
	
	TIM_OCInitStructure.TIM_Pulse = 600; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 高电平有效
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); //根据指定的参数初始化外设 TIMx
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH3 预装载使能
	
	
	TIM_OCInitStructure.TIM_Pulse = 800; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 高电平有效
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); //根据指定的参数初始化外设 TIMx
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH4 预装载使能
	
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //使能 TIMx 在 ARR 上的预装载寄存器
//	TIM_CtrlPWMOutputs(TIM4,ENABLE);  //MOE 主输出使能,高级定时器必须开启
	TIM_Cmd(TIM4, ENABLE); //使能 TIMx
}


/**
TIM_SetCompare1(TIM4,500);
TIM_SetCompare2(TIM4,500);
TIM_SetCompare3(TIM4,500);
TIM_SetCompare4(TIM4,500);
设置各个通道的占空比，占空比为：500/arr，main函数里arr设置为899,则占空比为500/899
**/