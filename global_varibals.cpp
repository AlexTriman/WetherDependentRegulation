/*
 * global_varibals.cpp
 *
 * Created: 21.08.2015 0:52:16
 *  Author: notebook
 */ 

#include "global_varibals.h"



void Total_ini (void)
{
	IND_Init();			
	Menu_Ini();
	
	
	Sounder_port_ini();
	
	Atmega16Timer16bitIni ();
	Timer2Atmega16RTC_ini();
	Buttons_initial();
	//Int1Ini_interrupt_falling_edge();
}
