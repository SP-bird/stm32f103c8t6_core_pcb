#include "app_oled.h"
#include "delay.h"
#include "bmp.h"
void app_oled_test(void)
{
	u8 t;
	t=' ';
	OLED_Clear();
		OLED_ShowCHinese(0,0,0);//��
		OLED_ShowCHinese(18,0,1);//��
		OLED_ShowCHinese(36,0,2);//԰
		OLED_ShowCHinese(54,0,3);//��
		OLED_ShowCHinese(72,0,4);//��
		OLED_ShowCHinese(90,0,5);//��
		OLED_ShowCHinese(108,0,6);//��
		OLED_ShowString(6,3,"0.96' OLED TEST",16);
		//OLED_ShowString(8,2,"ZHONGJINGYUAN");  
	 //	OLED_ShowString(20,4,"2014/05/01");  
		OLED_ShowString(0,6,"ASCII:",16);  
		OLED_ShowString(63,6,"CODE:",16);  
		OLED_ShowChar(48,6,t,16);//��ʾASCII�ַ�	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ 	
			delay_ms(1000);
//		delay_ms(8000);

//					delay_ms(8000);
//		delay_ms(8000);
//		delay_ms(8000);
		OLED_DrawBMP(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ��ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
//		delay_ms(8000);
//					delay_ms(8000);
//		delay_ms(8000);
//		delay_ms(8000);
//		OLED_DrawBMP(0,0,128,8,BMP1);
//		delay_ms(8000);
//					delay_ms(8000);
//		delay_ms(8000);
//		delay_ms(8000);
}