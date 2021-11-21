#include "app_wifi.h"
#include "wifi.h"
#include "usart2.h"
#include "delay.h"

char  Data_buff[2048];  //���ݻ�����
char  Data_len[5];      //���ݳ��Ȼ�����
char  Data_id[5];       //���ݷ����ߵ�id������

void app_wifi_init(void)
{
	Usart2_Init(115200);            //����2���ܳ�ʼ����������115200	
	
	WiFi_ResetIO_Init();            //��ʼ��WiFi�ĸ�λIO
    while(WiFi_InitServer_AP()){    //ѭ������ʼ����������������ֱ���ɹ�
		delay_ms(200);              //��ʱ
	}      
	WiFi_RxCounter=0;                           //WiFi������������������                        
	memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //���WiFi���ջ����� 
}

void app_wifi_test(void)
{
		WiFi_Get_LinkSta();                               //������޿ͻ������ӻ��ǶϿ�
		if(WiFi_Get_Data(Data_buff,Data_len,Data_id)){    //��������		
			printf("����id:%s��%s�ֽ����ݵ���\r\n",Data_id,Data_len);   //������ʾ��Ϣ
			printf("����:%s\r\n",Data_buff);                            //������ʾ��Ϣ
			WiFi_SendData(Char_to_Hex(Data_id,strlen(Data_id)),Data_buff,strlen(Data_buff),500);//5s�ķ��ͳ�ʱʱ�䣬��������
		}
}
