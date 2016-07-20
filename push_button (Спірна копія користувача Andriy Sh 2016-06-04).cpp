/*
 * push_button.cpp
 *
 * Created: 17.11.2015 13:24:00
 *  Author: Alex
  
 
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "global_varibals.h"
#include "push_buttons.h"
#include "digitsdisplay.h"
#include <avr/delay.h>
#include "Timing.h"
#include "menu.h"
#include "leds.h"

// initialisation of int0  for interrupts on falling edge
void Int0Ini_interrupt_falling_edge (void)
{
	DDR_COM &= ~(1 << PIN_COM);     // Clear the PD2 pin
    // PD2 (INT0 pin) is now an input

    PORT_COM |= (1 << PIN_COM);    // turn On the Pull-up
    // PD2 is now an input with pull-up enabled
	
	MCUCR |= (1 << ISC01);    // set INT0 to trigger on falling edge logic change
    GICR |= (1 << INT0);      // Turns on INT0

    sei();                    // turn on interrupts
}


void Int1Ini_interrupt_rising_edge (void)
{
	DDR_COM &= ~(1 << PIN_COM);     // Clear the PD2 pin
	// PD2 (INT0 pin) is now an input

	PORT_COM |= (1 << PIN_COM);    // turn On the Pull-up
	// PD2 is now an input with pull-up enabled
	
	MCUCR |= (1 << ISC11)|(1 << ISC10);    // set INT0 to trigger on falling edge logic change
	GICR |= (1 << INT1);      // Turns on INT1

	sei();                    // turn on interrupts
}

void Int1Ini_interrupt_falling_edge (void)
{
	DDR_COM &= ~(1 << PIN_COM);     // Clear the PD2 pin
	// PD2 (INT0 pin) is now an input

	PORT_COM |= (1 << PIN_COM);    // turn On the Pull-up
	// PD2 is now an input with pull-up enabled
	
	MCUCR |= (1 << ISC11);
	MCUCR &= ~(1 << ISC10);    // set INT0 to trigger on falling edge logic change
	GICR |= (1 << INT1);      // Turns on INT0

	sei();                    // turn on interrupts
}

void Int1Ini_interrupt_low_level (void)
{
	DDR_COM &= ~(1 << PIN_COM);     // Clear the PD2 pin
	// PD2 (INT0 pin) is now an input

	PORT_COM |= (1 << PIN_COM);    // turn On the Pull-up
	// PD2 is now an input with pull-up enabled
	
	MCUCR &= ~((1 << ISC11)|(1 << ISC10));    // set INT0 to trigger on falling edge logic change
	GICR |= (1 << INT1);      // Turns on INT0

	sei();                    // turn on interrupts
}

void Int1Ini_interrupt_logicChange (void)
{
	DDR_COM &= ~(1 << PIN_COM);     // Clear the PD3 pin
	// PD2 (INT0 pin) is now an input

	PORT_COM |= (1 << PIN_COM);    // turn On the Pull-up
	// PD2 is now an input with pull-up enabled
	
	MCUCR |= (0 << ISC11)|(1 << ISC10);    // set INT0 to trigger on falling edge logic change
	GICR |= (1 << INT1);      // Turns on INT1

	sei();                    // turn on interrupts
}

void Buttons_initial (void)
{
	
	PORT_COM &= ~(1 << PIN_COM);   // Pull up the resistor
	DDR_COM |= (1 << PIN_COM);     // Clear the PD3 pin   as input
	
	//set buttons' ports direction as output and put 0
	
	PORT_ESC  |=  (1 << PIN_ESC);
	PORT_DOWN  |=  (1 << PIN_DOWN);
	PORT_UP    |=  (1 << PIN_UP);
	PORT_ENTER |=  (1 << PIN_ENTER);
	
	DDR_ESC    &= ~(1 << PIN_ESC);
	DDR_DOWN  &= ~ (1 << PIN_DOWN);
	DDR_UP    &= ~ (1 << PIN_UP);
	DDR_ENTER  &= ~ (1 << PIN_ENTER);	
	
}

uint16_t longpress_check(void)
{
	static uint8_t counts=0;
	if (button_G == DOWN || button_G == UP)
	{
		blick_screen_G=false;
		 counts++;
	}
	else counts=0;
	if (counts>20)
	{
		blick_screen_G=false;
		return BUTTONS_PERIOD_CHECK/10;
	}
	else if (counts>5)
	{
		blick_screen_G=false;
		return BUTTONS_PERIOD_CHECK/2;
	}	
	else return BUTTONS_PERIOD_CHECK;
}

repeatingHandler long_pressing;
//repeatingHandler checking_switches;


void Buttons_qustioning (void)
{
	//static bool checking = false;
	static uint16_t period = BUTTONS_PERIOD_CHECK;	
	static bool button_press_happend = false;
	//static bool reaction_done = false;	
	static bool button_unpress_happend = false;
	//uint8_t count=0;
	//const uint16_t checking_period = 35;
	
	 if (switches_ask.repeat(period))
		 {
			button_G = PressedButton();					
			//if ((button_G==ENTER||button_G==ESC)&&selectedMenuItem->display_option!=EDIT_PARAMETER&&first_time)  //if we are not in editing mode then slow down qustioning buttons
		    if (!UNPRESSED)
			{				
				if (button_press_happend) button_press_happend = false;
				else button_press_happend=true;
				if (button_unpress_happend) 
				{
					button_press_happend=true;
					button_unpress_happend=false;
				}
			}
			else
			{
				button_unpress_happend = true;								
			}
		 }	
	
	if (button_press_happend)  // repeating period
	{
		button_G = PressedButton();
		keyMenu(button_G);
		RenewScreen();
		//period=longpress_check();	
		Beep();	 				
			/*if ((button_G==ENTER||button_G==ESC)&&selectedMenuItem->display_option!=EDIT_PARAMETER&&first_time)  //if we are not in editing mode then slow down qustioning buttons
			{
				first_time = true;
			}
			else
			{
				 			
				 first_time=true;
		}*/
		//count++;
		button_press_happend = false;
	}	
}


ButtonValues PressedButton (void)
{
	//check out the  button	esc
			unsigned char r = 0;
			char a=0;
			char b=0;
		    r = ~PINx_ESC;
			r &= (1<<PIN_ESC);  //  //here we get the PIN_ESC, other bits we make 0
			
			for (char i=1; i<5; i++)
			{		
					if(r == (1<<PIN_ESC)) a++;	
					else b++;
					//_delay_ms(2);					
			}
			if (a>b) return ESC;
			
			//chek out the button -
			a=0;
			b=0;
			r = ~PINx_DOWN;
			r &= (1<<PIN_DOWN);  //  //here we get the PIN_DOWN, other bits we do 0
			for (char i=1; i<5; i++)
			{
				if(r == (1<<PIN_DOWN)) a++;
				else b++;
				//_delay_ms(2);
			}		
			if (a>b)  return DOWN;
				 
				 
			
		
			//check out the button +
			r = ~PINx_UP;
			r &= (1<<PIN_UP);  //  //here we get the PIN_DOWN, other bits we do 0
			a=0;
			b=0;
			for (char i=1; i<5; i++)
			{
				if(r == (1<<PIN_UP)) a++;
				else b++;
				//_delay_ms(2);
			}
			if (a>b) return UP;		
				
			
		
			//check out the button ENTER
			r = ~PINx_ENTER;
			r &= (1<<PIN_ENTER);  //  //here we get the PIN_Enter, other bits we do 0
			a=0;
			b=0;
			for (char i=1; i<5; i++)
			{
				if(r == (1<<PIN_ENTER)) a++;
				else b++;
				//_delay_ms(2);
			}
			if (a>b) return ENTER;
	
		
		
		return UNPRESSED;
}

// in main: cheeking the buttons if any has been pressed
repeatingHandler longpressWait;
repeatingHandler longpressRepeats;

void LongPressButtonCheck (ButtonValues the_button)
{
	static bool start = false;
	
	if (the_button == UNPRESSED ||the_button == ESC || the_button == ENTER) //if not +- buttons pressed 
	{
		start = false;		
		return;
	}
	else
	{
		
		if (start==false) 
		{
			if (longpressWait.repeat(960))	start = true;  //wait until pressing has been going for more then 1s, then can start			
			return;
		}
		else 
		{
			if (longpressRepeats.repeat(400))  //make changes every 300ms editing 
			{				
				keyMenu(the_button);
				//renew display info				
				LightUpLed(chosen_led_G);				
				RenewScreen();
			}
		}	
		
	}
	
}

void Lock_buttons (void)
{	
		GICR &= ~(1 << INT1);      // Turns off INT1 interrupts 
	
		PORT_COM &= ~(1 << PIN_COM);   // Pull up the resistor
		DDR_COM |= (1 << PIN_COM);     // Clear the PD2 pin   as input		
		
		PORT_ESC   &= ~ (1 << PIN_ESC);
		PORT_DOWN  &= ~ (1 << PIN_DOWN);
		PORT_UP    &= ~ (1 << PIN_UP);
		PORT_ENTER &= ~ (1 << PIN_ENTER);
		
		DDR_ESC   |= (1 << PIN_ESC);
		DDR_DOWN  |= (1 << PIN_DOWN);
		DDR_UP    |= (1 << PIN_UP);
		DDR_ENTER |= (1 << PIN_ENTER);
		
}