/*-------------------------------------------------------------
	operation.c
	operation in all case
--------------------------------------------------------------*/

#include "main.h"
#include "port.h"

#include "operation.h"
#include "other.h"
#include "voice.h"
#include "battery.h"
#include "delay.h"

/*------- Public variable declarations --------------------------*/
extern bit slave_away_speech_EN;      
extern bit slave_nearby_speech_EN;     
extern bit position_sensor_EN;  		//位置传感器，即倒地抬起传感器总开关，1的时候，检测这两个传感器
extern bit slave_away;					//模式选择位，1则用模式1,2则用模式2,3则为模式3
extern bit magnet_CW_EN;					//电磁铁顺时针转动使能，转动一次后复位为0
extern bit fell_flag;						//判断主机倒下后，置1
extern bit raised_flag;					//判断主机被抬起后，置1
extern tByte sensor_trigger_count;		//传感器触发计数
extern tByte sensor_1ststage_count;	//传感器第一阶段判断低电平的计数
extern tByte leave_count;					// increment every 2s, reset for every success communication
extern bit raised_fell_once_flag;			//raised_fell_flag是否曾经标志过，如果标志过则置1.然后主机被恢复倒地或者恢复抬起时，此标志位复位。
extern bit raised_fell_flag;					//倒地或者抬起触发后，此标志位置1
extern bit host_stolen_alarm1_EN;      //判断为被盗报警后的第一段语音使能
extern bit host_stolen_alarm2_EN;      //判断为被盗报警后的第二段语音使能
extern tByte host_stolen_alarm1_count;		//判断为被盗报警后的第一段语音次数
extern tByte host_stolen_alarm2_count;		//判断为被盗报警后的第二段语音次数
extern bit stolen_alarm_flag;					// when host been touch 3 times, this flag 1 before alarm voice present, not to detect sensor for 1st voice alarm.
extern tWord sensor_3rdstage_time;			//传感器进入第三阶段的时间，
extern tByte sensor_3rdstage_effcount;		//传感器进入第三阶段后，有效触碰次数的计数
extern tByte sensor_3rdstage_count;			//传感器进入第三阶段后，低电平的计数
extern tWord sensor_3rdstage_interval;		//传感器在第三阶段中，每次有效低电平计数之间的时间间隔。在这期间的低电平不认为有效。
extern tWord sensor_2ndstage_time;		//传感器进入第二阶段后流逝时间的计数
extern tByte sensor_2ndstage_count;		//传感器进入第二阶段检测时，计算低电平的时间
extern tByte nearby_away_interval;		//附机离开和靠近时，语音提示和开关锁的时间间隔
extern bit slave_nearby_EN;			// 作为slave靠近后操作的使能
extern tByte slave_nearby_operation_count;	// 作为slave靠近后操作的次数
extern tByte key_rotated_on_flag;			//电动车开启关闭标志位，1表示电动车开启了，0表示电动车关闭了
extern tWord ADC_check_result;		//作为AD检测值
extern tByte wire_broken_count;		// 作为断线后的时间检测

/*-----------------------------------------
	slave_away_operation().c
	
	operation for slave is away
------------------------------------------*/
void slave_away_operation(void)
	{
	// turn off the magnet 
	magnet_ACW();
	
	// speech for slave away
	slave_away_speech();
	
	
	// enable position sensor(vertical and horizontal) and vibration sensor
	position_sensor_EN=1;	
	sensor_EN = 1;
	// reset relatively sensor count
	sensor_trigger_count=0;
	sensor_1ststage_count=0;
	
	// delay time, avoid sensor trigger on.
	Delay(20);
	}

/*----------------------------------------------------------------------
		slave_nearby_operation()
		operation for slave is nearby
----------------------------------------------------------------------*/
void slave_nearby_operation(void)
	{
	// enable position sensor(vertical and horizontal) and vibration sensor
	position_sensor_EN = 0;	
	sensor_EN = 0;

	// turn on the magnet
	magnet_CW();

	// speech for slave nearby
	slave_nearby_speech();
	// handle with battery status 
	verifybattery(ADC_check_result);					
	// rotate on speech
	key_rotate_on_speech();
	nearby_away_interval = 0;
	
	// reset all the flag in sensor
	fell_flag=0;  
	raised_flag=0;
	sensor_trigger_count = 0;
	sensor_1ststage_count = 0;
	sensor_2ndstage_count = 0;
	sensor_2ndstage_time = 0;
	sensor_3rdstage_time = 0;
	sensor_3rdstage_interval = 0;
	sensor_3rdstage_count = 0;
	sensor_3rdstage_effcount = 0;
	stolen_alarm_flag = 0;
	host_stolen_alarm1_EN = 0;
	host_stolen_alarm1_count = 0;
	host_stolen_alarm2_EN = 0;
	host_stolen_alarm2_count = 0;
	
	raised_fell_flag = 0;
	
	// reset the wire broken count
	wire_broken_count = 0;
	}
	
/*---------------------------------------------------
	end of file
----------------------------------------------------*/
