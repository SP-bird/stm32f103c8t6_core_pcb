#include "app_wifi.h"
#include "wifi.h"
#include "usart2.h"
#include "delay.h"

char  Data_buff[2048];  //数据缓冲区
char  Data_len[5];      //数据长度缓冲区
char  Data_id[5];       //数据发送者的id缓冲区

void app_wifi_init(void)
{
	Usart2_Init(115200);            //串口2功能初始化，波特率115200	
	
	WiFi_ResetIO_Init();            //初始化WiFi的复位IO
    while(WiFi_InitServer_AP()){    //循环，初始化，建立服务器，直到成功
		delay_ms(200);              //延时
	}      
	WiFi_RxCounter=0;                           //WiFi接收数据量变量清零                        
	memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //清空WiFi接收缓冲区 
}

void app_wifi_test(void)
{
		WiFi_Get_LinkSta();                               //检测有无客户端连接或是断开
		if(WiFi_Get_Data(Data_buff,Data_len,Data_id)){    //接收数据		
			printf("连接id:%s有%s字节数据到来\r\n",Data_id,Data_len);   //串口显示信息
			printf("数据:%s\r\n",Data_buff);                            //串口显示信息
			WiFi_SendData(Char_to_Hex(Data_id,strlen(Data_id)),Data_buff,strlen(Data_buff),500);//5s的发送超时时间，发送数据
		}
}
