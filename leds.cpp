/*
 * leds.cpp
 *
 * Created: 02.01.2016 10:59:08
 *  Author: notebook
 */ 
/* have to be declared in main or globalvariebels.h
enum led_num
{
	TCOMF_LED,
	TECO_LED,
	TFLOW_LED,
	TSET_LED,
	TOUTSIDE_LED,
	PROG_LED,
	MENU_LED	
};
*/
#include <avr/io.h>
#include "global_varibals.h"
#include "leds.h"
#include "Timing.h"

#define BLICKPERIOD 4

#define DDR_tcomf DDRC
#define PORT_tcomf PORTC
#define PIN_tcomf 4

#define DDR_teco DDRC
#define PORT_teco PORTC
#define PIN_teco 5

#define DDR_toutside DDRA
#define PORT_toutside PORTA
#define PIN_toutside 4

#define DDR_tflow DDRA
#define PORT_tflow PORTA
#define PIN_tflow 3

#define DDR_tset DDRD
#define PORT_tset PORTD
#define PIN_tset 0

#define DDR_prog DDRD
#define PORT_prog PORTD
#define PIN_prog 1

#define DDR_menu DDRD
#define PORT_menu PORTD
#define PIN_menu 2

void LightOutAll_Leds (void)
{
	PORT_tcomf &= ~(1<<PIN_tcomf);
	DDR_tcomf |= (1<<PIN_tcomf);
	
	PORT_teco &= ~(1<<PIN_teco);
	DDR_teco |= (1<<PIN_teco);
	
	PORT_toutside &= ~(1<<PIN_toutside);
	DDR_toutside |= (1<<PIN_toutside);
	
	PORT_tflow &= ~(1<<PIN_tflow);
	DDR_tflow |= (1<<PIN_tflow);
	
	PORT_tset &= ~(1<<PIN_tset);
	DDR_tset |= (1<<PIN_tset);
	
	PORT_prog &= ~(1<<PIN_prog);
	DDR_prog |= (1<<PIN_prog);
	
	PORT_menu &= ~(1<<PIN_menu);
	DDR_menu |= (1<<PIN_menu);
		
}
void LightUpLed (led_num led_number)
{
	LightOutAll_Leds ();
	switch (led_number)
	{
		case TCOMF_LED:
		PORT_tcomf |= (1<<PIN_tcomf);		
		DDR_tcomf |= (1<<PIN_tcomf);
		break;
		
		case TECO_LED:
		PORT_teco |= (1<<PIN_teco);
		DDR_teco |= (1<<PIN_teco);
		break;
		
		case TOUTSIDE_LED:
		PORT_toutside |= (1<<PIN_toutside);
		DDR_toutside |= (1<<PIN_toutside);
		break;
				
		case TFLOW_LED:
		PORT_tflow |= (1<<PIN_tflow);
		DDR_tflow |= (1<<PIN_tflow);
		break;
				
		case TSET_LED:
		PORT_tset |= (1<<PIN_tset);
		DDR_tset |= (1<<PIN_tset);
		break;
	
		case PROG_LED:
		PORT_prog |= (1<<PIN_prog);
		DDR_prog |= (1<<PIN_prog);
		break;
		
		case MENU_LED:
		PORT_menu |= (1<<PIN_menu);
		DDR_menu |= (1<<PIN_menu);
		break;
		
		case MO_LED:
		{			
		   static char count = 0;		  
		   	   
		   if (count < 1)
		   {
			PORT_tcomf |= (1<<PIN_tcomf);
			DDR_tcomf |= (1<<PIN_tcomf);			 
		   }
		   count++;				
		   if (count >=BLICKPERIOD) count = 0;  
		   break;
		}
			
		case TU_LED:
		{
			static char count = 0;			
			
			if (count < 1)
			{
				PORT_teco |= (1<<PIN_teco);
				DDR_teco |= (1<<PIN_teco);			
			}
			count++;
			if (count >=BLICKPERIOD) count = 0;  
			break;
		}
		
		case WE_LED:
		{
			static char count = 0;			
			
			if (count < 1)
			{
				PORT_toutside |= (1<<PIN_toutside);
				DDR_toutside |= (1<<PIN_toutside);			
			}
			count++;
			if (count >=BLICKPERIOD) count = 0;  
			break;
		}
		
		case TH_LED:
		{
			static char count = 0;			
			
			if (count < 1)
			{
				PORT_tflow |= (1<<PIN_tflow);
				DDR_tflow |= (1<<PIN_tflow);				
			}
			count++;
			if (count >=BLICKPERIOD) count = 0;  
			break;
		}
		
		case FR_LED:
		{
			static char count = 0;			
			
			if (count < 1)
			{
				PORT_tset |= (1<<PIN_tset);
				DDR_tset |= (1<<PIN_tset);		
			}
			count++;
			if (count >=BLICKPERIOD) count = 0;  
			break;
		}
		
		case SA_LED:
		{
			static char count = 0;			
			
			if (count < 1)
			{
				PORT_prog |= (1<<PIN_prog);
				DDR_prog |= (1<<PIN_prog);				
			}
			count++;
			if (count >=BLICKPERIOD) count = 0;  			
			break;
		}
		
		case SU_LED:
		{
			static char count = 0;
					
			if (count < 1)
			{
				PORT_menu |= (1<<PIN_menu);
				DDR_menu |= (1<<PIN_menu);				
			}
			count++;
			if (count >=BLICKPERIOD) count = 0;  
			break;
		}
		
		
		default:
		LightOutAll_Leds ();
	}
	
}