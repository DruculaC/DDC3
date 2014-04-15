/*---------------------------------------------------
	Delay.c (v1.00)
	
	Delay functions
---------------------------------------------------*/	

#include "main.h"
#include "port.h"

#include "Delay.h"

/*---------------------------------------------------
	Delay(tWord n)
	
	延迟程序
----------------------------------------------------*/	

void Delay(tWord n)
	{
	tWord x;
	while(n--)
		{
		x=5000;
		while(x--);
		}
	}

/*---------------------------------------------------
	Delay3()
	延迟程序
--------------------------------------------------*/

void Delay3(tWord t)		//t=1时，延迟100us左右
	{
	tWord i;
	tByte j;
	for(i=0;i<t;i++)		                                
	for(j=0;j<42;j++);
	}
	
/*--------------------------------------------------
	delay_ms()
	
	延迟约为1ms的子程序
----------------------------------------------------*/

void delay_ms(tWord count)
{
	tWord i, j;
	for(i=0;i<count;i++)
	{
		for(j=0;j<100;j++);
	}
}

/*--------------------------------------------------
	delay_us()
	
	延迟约为1us的子程序
----------------------------------------------------*/

void delay_us(tWord count1)
	{
	tWord i;
	tByte j;
	for(i=0;i<count1;i++)
		{
		for(j=0;j<4;j++);
		}
	}

/*---------------------------------------------------
	end of file
----------------------------------------------------*/
