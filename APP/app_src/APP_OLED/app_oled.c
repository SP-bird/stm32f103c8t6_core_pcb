#include "app_oled.h"
#include "delay.h"
#include "bmp.h"
void app_oled_test(void)
{
	u8 t;
	t=' ';
	OLED_Clear();
		OLED_ShowCHinese(0,0,0);//天
		OLED_ShowCHinese(18,0,1);//生
		OLED_ShowCHinese(36,0,2);//我
		OLED_ShowCHinese(54,0,3);//材
		OLED_ShowCHinese(72,0,4);//必
		OLED_ShowCHinese(90,0,5);//有
		OLED_ShowCHinese(108,0,6);//用
		OLED_ShowString(6,2,"good good study day day up",16);
		//OLED_ShowString(8,2,"ZHONGJINGYUAN");  
	 //	OLED_ShowString(20,4,"2014/05/01");  
		OLED_ShowString(0,6,"ASCII:",16);  
		OLED_ShowString(63,6,"CODE:",16);  
		OLED_ShowChar(48,6,t,16);//显示ASCII字符	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
//			delay_ms(1000);
//		delay_ms(5000);
		OLED_Clear();
//					delay_ms(8000);
//		delay_ms(8000);
//		delay_ms(8000);
//		OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
		OLED_DrawBMP(0,0,128,8,BMP2);
//		delay_ms(8000);
//					delay_ms(8000);
//		delay_ms(5000);
//		delay_ms(8000);
//		OLED_DrawBMP(0,0,128,8,BMP1);
//		delay_ms(8000);
//					delay_ms(8000);
//		delay_ms(8000);
//		delay_ms(8000);
}


void app_oled_test1(int num)
{
	if (num % 3 == 0) {
		OLED_Clear();
		OLED_ShowCHinese(0,0,0);//天
		OLED_ShowCHinese(18,0,1);//生
		OLED_ShowCHinese(36,0,2);//我
		OLED_ShowCHinese(54,0,3);//材
		OLED_ShowCHinese(72,0,4);//必
		OLED_ShowCHinese(90,0,5);//有
		OLED_ShowCHinese(108,0,6);//用
		OLED_ShowString(6,2,"good good study day day up",16);
	} else if (num % 3 == 1)
	{
		OLED_Clear();
		OLED_DrawBMP(0,0,128,8,BMP1);
	} else {
		OLED_Clear();
		OLED_DrawBMP(0,0,128,8,BMP2);
	}
}
