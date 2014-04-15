/*---------------------------------------------------
	Battery.c (v1.00)
	
	µç³ØµçÁ¿ÅÐ¶Ï
---------------------------------------------------*/	

#include "main.h"
#include "port.h"

#include "Battery.h"
#include "voice.h"
#include "Delay.h"

/*------ public variable -----------------------------------*/
extern tByte key_rotated_on_flag;

/*----------------------------------------------------
	verifybattery()
	voice alarm for battery status
-----------------------------------------------------*/

void verifybattery(tWord Check2)
	{	
	// battery is sufficient, battery > 54.6V, 3.18V/4.04V
//	if((Check2 >= 0x326))
	if((Check2 >= 0x316))
		{
		voice_EN = 1;
		SC_Speech(28);  	
		Delay(50);
		voice_EN = 0;
		}
   // 20km, 52V < battery < 54.6, 3.08V/4.04V
//	else if((Check2 < 0x322)&&(Check2 >= 0x30c))		
	else if((Check2 < 0x312)&&(Check2 >= 0x2fc))		
		{
		voice_EN = 1;
		SC_Speech(10);  
		Delay(80);
		voice_EN = 0;
		}
	// 15km, 50V < battery < 52V, 2.98V/4.04V 
//	else if((Check2 < 0x309)&&(Check2 >= 0x2f3))		
	else if((Check2 < 0x2f9)&&(Check2 >= 0x2e3))		
		{
		voice_EN = 1;
		SC_Speech(9);  	
		Delay(80);
		voice_EN = 0;
		}
	// 10km, 48V < battery <50V, 2.88V/4.04V
//	else if((Check2 < 0x3f0)&&(Check2 >= 0x2da))		
	else if((Check2 < 0x2e0)&&(Check2 >= 0x2ca))		
		{
		voice_EN = 1;
		SC_Speech(8);  	
		Delay(80);
		voice_EN = 0;
		}
	// 5km, 46V < battery < 48V, 2.78V/4.04V
//	else if((Check2 < 0x2d7)&&(Check2 >= 0x2c0))		
	else if((Check2 < 0x2c7)&&(Check2 >= 0x2b0))		
		{
		voice_EN =1;
		SC_Speech(7);  	
		Delay(80);
		voice_EN = 0;
		}
	// battery is low, battery < 46V
//	else if(Check2 < 0x2bd)
	else if(Check2 < 0x2ad)
		{
		motorBAT_low_speech();
		}
	}

/*---------------------------------------------------
	end of file
----------------------------------------------------*/