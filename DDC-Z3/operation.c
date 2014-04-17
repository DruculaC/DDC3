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
extern bit position_sensor_EN;  		//λ�ô�������������̧�𴫸����ܿ��أ�1��ʱ�򣬼��������������
extern bit slave_away;					//ģʽѡ��λ��1����ģʽ1,2����ģʽ2,3��Ϊģʽ3
extern bit magnet_CW_EN;					//�����˳ʱ��ת��ʹ�ܣ�ת��һ�κ�λΪ0
extern bit fell_flag;						//�ж��������º���1
extern bit raised_flag;					//�ж�������̧�����1
extern tByte sensor_trigger_count;		//��������������
extern tByte sensor_1ststage_count;	//��������һ�׶��жϵ͵�ƽ�ļ���
extern tByte leave_count;					// increment every 2s, reset for every success communication
extern bit raised_fell_once_flag;			//raised_fell_flag�Ƿ�������־���������־������1.Ȼ���������ָ����ػ��߻ָ�̧��ʱ���˱�־λ��λ��
extern bit raised_fell_flag;					//���ػ���̧�𴥷��󣬴˱�־λ��1
extern bit host_stolen_alarm1_EN;      //�ж�Ϊ����������ĵ�һ������ʹ��
extern bit host_stolen_alarm2_EN;      //�ж�Ϊ����������ĵڶ�������ʹ��
extern tByte host_stolen_alarm1_count;		//�ж�Ϊ����������ĵ�һ����������
extern tByte host_stolen_alarm2_count;		//�ж�Ϊ����������ĵڶ�����������
extern bit stolen_alarm_flag;					// when host been touch 3 times, this flag 1 before alarm voice present, not to detect sensor for 1st voice alarm.
extern tWord sensor_3rdstage_time;			//��������������׶ε�ʱ�䣬
extern tByte sensor_3rdstage_effcount;		//��������������׶κ���Ч���������ļ���
extern tByte sensor_3rdstage_count;			//��������������׶κ󣬵͵�ƽ�ļ���
extern tWord sensor_3rdstage_interval;		//�������ڵ����׶��У�ÿ����Ч�͵�ƽ����֮���ʱ�����������ڼ�ĵ͵�ƽ����Ϊ��Ч��
extern tWord sensor_2ndstage_time;		//����������ڶ��׶κ�����ʱ��ļ���
extern tByte sensor_2ndstage_count;		//����������ڶ��׶μ��ʱ������͵�ƽ��ʱ��
extern tByte nearby_away_interval;		//�����뿪�Ϳ���ʱ��������ʾ�Ϳ�������ʱ����
extern bit slave_nearby_EN;			// ��Ϊslave�����������ʹ��
extern tByte slave_nearby_operation_count;	// ��Ϊslave����������Ĵ���
extern tByte key_rotated_on_flag;			//�綯�������رձ�־λ��1��ʾ�綯�������ˣ�0��ʾ�綯���ر���
extern tWord ADC_check_result;		//��ΪAD���ֵ
extern tByte wire_broken_count;		// ��Ϊ���ߺ��ʱ����
extern bit battery_stolen_EN;			// ��Ϊ��ر�����ʹ�ܶ�
extern tByte battery_stolen_count;	// ��Ϊ��ر����ı�������

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
	
	// reset battery stolen
	battery_stolen_EN = 0;
	battery_stolen_count = 0;
	}
	
/*---------------------------------------------------
	end of file
----------------------------------------------------*/
