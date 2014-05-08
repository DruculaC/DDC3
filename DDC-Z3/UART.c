#include "main.h"
#include "port.h"

#include "uart.h"


/*
�������� void InitUART()
���ܣ� 	��ʼ��UART
˵����
��ڲ�������
����ֵ��  ��
*/
void InitUART()
{
	AUXR1 &=0xbf ; 
	SCON=0x5a;
	TMOD=0x20;
	TH1=TL1=-(OSC_FREQ/12/32/BAUD);
	TR1=1;
}
/*
�������� void SendData(BYTE dat)
���ܣ� 	���ͺ���
˵����
��ڲ�����Ҫ���͵��ֽ�
����ֵ��  ��
*/

void SendData(unsigned char dat)
{
	SBUF=dat;
	while(!TI);TI=0;	
}

/*
��������void SendNByte(BYTE *buf,BYTE len)
���ܣ� ���Ͷ���ֽ�
˵����
��ڲ�����Ҫ���͵����ݵ�ַ�����͵��ֽڳ���
����ֵ�� ��
*/
void SendNByte(unsigned char *buf, unsigned char len)
{
	while(len--)
	{
		SendData(*buf++);
	}
}


//
///*
//��������BYTE GetData()
//���ܣ� 	���պ���
//˵����
//��ڲ��� ����
//����ֵ�� ���յ�������
//*/
//unsigned char GetData(void)
//{
//	unsigned char datt;
//	while(!RI);RI=0;
//	datt=SBUF;
//	return datt;
//}




///*
//��������WORD  GainSum(BYTE *oneData,BYTE dataLen)
//���ܣ�	��ͺ�������Ϊ��żУ��
//˵����
//��ڲ��������յ����ݲ���	,���ݳ���
//����ֵ��  У������
//*/
//unsigned int  GainSum(unsigned char *oneData,unsigned char dataLen)
//{
//	unsigned char i=0;
//	unsigned int between=0;
//
//
//	for(i=0;i<dataLen;i++)
//	{
//	between=*oneData+between;
//	oneData+=1;
//	}
//
//	return between;
//}












