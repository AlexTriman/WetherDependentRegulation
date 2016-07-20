/*
 * comparator.cpp
 *
 * Created: 07.04.2016 15:52:21
 *  Author: Alex
 */ 


#include <avr/io.h>
#include <avr/sleep.h>
#include "global_varibals.h"
#include "sleeping.h"
#include "sensor.h"
#include "digitsdisplay.h"   //LightOutAll()
#include "climate.h"   //StopServo()
#include "push_buttons.h"  //  Lock_buttons() 



void Vcc_chek_pin_ini (void)
{
	// set up pins
	DDRA &= ~(1<<PINA2);		
	PORTA &= ~(1<<PINA2);
	
	//set up comparator	
	
}



void sleeping (void)
{
	float adc = GetAverageADCValue(2,40, VCC);	
	float Vcc = adc*V_BATT_REF/1024;   //напруга реальна виміряна  2.56/1024 = 0.0025	
	
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	
	if (Vcc < U_POROGOVE)
	{	
		
		//disable relays
		StopServo();
		//disable display
		FullOffIND();
		TIMSK &= ~(1<<OCIE1A );  // Когда этот бит установлен в 0  прерывания 16битн таймера запрещени
		//desable all leds		
		LightOutAll_Leds();				
		//disable buttons
		Lock_buttons(); 
		//disable display
		
			
		
		cli();
		sleep_enable();			
		sei();
		sleep_cpu();
		// here we sleep until interrupt				
		sleep_disable();
		while ( (V_BATT_REF*GetAverageADCValue(2,40,VCC)/1024) < U_POROGOVE)
		{
			sleep_enable();
			sei();
			sleep_cpu();
			// here we sleep until interrupt
			sleep_disable();
		} 
		Total_ini();									
	}	
	
	
	
}

