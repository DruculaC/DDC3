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
	// battery is sufficient, battery > 51.2V, 3.53V/4.95V
//	if((Check2 >= 0x326))
	if((Check2 >= 0x2da))
		{
		voice_EN = 1;
		SC_Speech(28);  	
		Delay(50);
		voice_EN = 0;
		}
   // 20km, 50.1V < battery < 51.2, 3.47V/4.95V
//	else if((Check2 < 0x322)&&(Check2 >= 0x30c))		
	else if((Check2 < 0x2da)&&(Check2 >= 0x2cd))		
		{
		voice_EN = 1;
		SC_Speech(10);  
		Delay(80);
		voice_EN = 0;
		}
	// 15km, 49V < battery < 50.1V, 3.42V/4.95V 
//	else if((Check2 < 0x309)&&(Check2 >= 0x2f3))		
	else if((Check2 < 0x2cd)&&(Check2 >= 0x2c3))		
		{
		voice_EN = 1;
		SC_Speech(9);  	
		Delay(80);
		voice_EN = 0;
		}
	// 10km, 48V < battery <49V, 3.36V/4.95V
//	else if((Check2 < 0x3f0)&&(Check2 >= 0x2da))		
	else if((Check2 < 0x2c3)&&(Check2 >= 0x2b7))		
		{
		voice_EN = 1;
		SC_Speech(8);  	
		Delay(80);
		voice_EN = 0;
		}
	// 5km, 47V < battery < 48V, 3.31V/4.95V
//	else if((Check2 < 0x2d7)&&(Check2 >= 0x2c0))		
	else if((Check2 < 0x2b7)&&(Check2 >= 0x2ac))		
		{
		voice_EN =1;
		SC_Speech(7);  	
		Delay(80);
		voice_EN = 0;
		}
	// battery is low, battery < 47V
//	else if(Check2 < 0x2bd)
	else if(Check2 < 0x2ac)
		{
		motorBAT_low_speech();
		}
	}

/*---------------------------------------------------
	end of file
----------------------------------------------------*/