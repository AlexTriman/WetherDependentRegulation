/*
 * RTC.cpp
 *
 * Created: 09.04.2016 0:08:51
 *  Author: Alex
 */ 

#include "RTC.h"
#include "global_varibals.h"

void Timer2Atmega16RTC_ini()
{
	 _delay_ms(500);
	
	ASSR |= (1<<AS2);  // the sorce of clock asynchronos clock from pin
	
	TCNT2 = 0x00; //initial value setting up
	/*The Output Compare Register contains an 8-bit value that is continuously compared with the counter value
	(TCNT2). A match can be used to generate an output compare interrupt, or to generate a waveform output on
	the OC2 pin.*/
	TCCR2 = 0x05; //Устанавливаем коэффициент деления равным 128. so we get 32.768kHz/128 = 256   
	OCR2  = 0x00;  
	
	// Ждем готовности таймера.
	while (ASSR & ((1<<TCN2UB) | (1<<OCR2UB) | (1<<TCR2UB)));

	// Разрешаем прерывание от Таймера 2.
	TIMSK |= (1<<TOIE2);  //enable interrupt when overflow 
	// Разрешаем прерывания глобально.
	sei();
}

