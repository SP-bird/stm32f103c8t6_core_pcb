资源配置
1、宏开关  user/config.h

2、定时器资源说明

	timer2 向上计数，可以通过配置TIMER_NUMBERS，改变向上计数的定时器全局变量的个数，或者说可以用于计数功能的软件定时器个数
	timer3 生成多个软件定时器，应用层使用，数量可以配置
	timer4 作为PWM的定时器，如果需要用定时器3，则不能打开PWM
	
3、PWM对应引脚
	PB6 - TIM4_CH1
	PB7 - TIM4_CH2
	PB8 - TIM4_CH3
	PB9 - TIM4_CH4	

4、led对应引脚
	PC13 - LED0

5、key对应引脚
	PB5 - KEY0
	
6、打印串口
	PA9  -  USART1_TX
	PA10 - USART1_RX	

7、wifi
	PA2 - USART2_TX
	PA3 - USART2_RX	
	PA4 - rst
	
8、OLED
	PA5 - SCL
	PA7 - SDA

	
	
			
			
			
			
			
			
			
			
			
			
			
			
			
			