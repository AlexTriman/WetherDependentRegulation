/*
 * sounder.cpp
 *
 * Created: 22.02.2016 13:56:48
 *  Author: Alex
 */ 

#include <avr/io.h>

#include "sounder.h"
#include "global_varibals.h"


void Sounder_port_ini (void)
{		
	SOUNDER_PORT &= ~(1<<SOUNDER_PIN);
	SOUNDER_DDR |= (1<<SOUNDER_PIN);
	
}

void Beep (void)
{
	for (int i=0; i<300; i++)
	{
		SOUNDER_PORT |= (1<<SOUNDER_PIN);
		_delay_us (100);
		SOUNDER_PORT &= ~(1<<SOUNDER_PIN);
		_delay_us(80);
	}
}