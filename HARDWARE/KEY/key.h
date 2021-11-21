#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//读取按键0
#define KEY0_PRES 	1	//KEY0按下

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
