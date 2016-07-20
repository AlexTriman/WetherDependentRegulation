/*
 * comparator.cpp
 *
 * Created: 07.04.2016 15:52:21
 *  Author: Alex
 */ 


#include <avr/io.h>
#include "comparator.h"
#include "sensor.h"
#include <avr/sleep.h>
#include "digitsdisplay.h"   //LightOutAll()
#include "climate.h"   //StopServo()
#include "push_buttons.h"  //  Lock_buttons() 

#define U_POROGOVE 1.5

void Vcc_chek_pin_ini (void)
{
	// set up pins
	DDRA &= ~(1<<PINA2);		
	PORTA &= ~(1<<PINA2);
	//set up comparator	
	
}

void chekVCC_gosleep (void)
{
	float adc = GetAverageADCValue(2,10,Vinternal);
	
	float Vcc = (2.56*adc)/1024;   //напруга реальна виміряна
	
	if (Vcc < U_POROGOVE)
	{
		set_sleep_mode(SLEEP_MODE_PWR_SAVE);
		
		//desable display
		LightOutAll();
		//disable relays
		StopServo();
		
		//desable all leds
		LightOutAll_Leds();
		//disable sounder
		
		//disable buttons
		Lock_buttons (); 
		
		sei();
		sleep_enable();	
		
	}
	
}


