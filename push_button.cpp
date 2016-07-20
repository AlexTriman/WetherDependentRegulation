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





void Buttons_qustioning (void)
{
	
	static uint16_t period = BUTTONS_PERIOD_CHECK;	
				 
	if (switches_ask.repeat(period)) button_G = PressedButton();  // repeating period
	button_reaction_Method(button_G);
}



void button_reaction_Method (ButtonValues sw_button)
{
	static bool wait_unpressing = false;
	static uint16_t period = BUTTON_PERIOD_REACTION;
	
	if (wait_unpressing)
	{
		if (button_G == UNPRESSED) wait_unpressing=false;				
	}
	else
	{
		if (button_G!=UNPRESSED)
		{
			wait_unpressing= buttonAction(button_G, &period);			
		}
		else 
		{
			period=longpress_check(sw_button);			
			wait_unpressing=false;
		}
	}		
}


bool wait_unpressingY_N (ButtonValues sw_button)
{
	if (  sw_button==ENTER||sw_button==ESC||
	     ((sw_button==DOWN||sw_button==UP)&&((selectedMenuItem->display_option) != EDIT_PARAMETER))
	   )
	{
		return true;
	}
	else return false;
}



repeatingHandler sw_button_action;
bool buttonAction (ButtonValues sw_button, uint16_t* period_p)
{
	if (sw_button_action.repeat (*period_p))
	{
		keyMenu(sw_button);			
		Beep();
		RenewScreen();
		*period_p=longpress_check(sw_button);		
		return wait_unpressingY_N(sw_button);
	}	
	return false;
}

uint16_t longpress_check(ButtonValues sw_button)
{
	static uint16_t counts_=0;
	
	
	if (sw_button == DOWN || sw_button == UP)
	{	
		blick_screen_G=false;
		counts_++;
	}
	else 
	{
		counts_=0;	
		RenewScreen();
	}
	
	if (counts_>20)
	{
		blick_screen_G=false;
		return BUTTON_PERIOD_REACTION/4;
	}
	else if (counts_>8)
	{
		blick_screen_G=false;
		return BUTTON_PERIOD_REACTION/2;
	}
	else return BUTTON_PERIOD_REACTION;
}

void chosenButtons(void)
{
	
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