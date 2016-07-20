/*
 * push_buttons.h
 *
 * Created: 17.11.2015 13:23:13
 *  Author: Alex
 */ 


#ifndef PUSH_BUTTONS_H_
#define PUSH_BUTTONS_H_

// set up ports for buttons


#define DDR_COM DDRD
#define PORT_COM  PORTD
#define PIN_COM  3

#define DDR_ESC DDRD
#define PORT_ESC  PORTD
#define PINx_ESC  PIND
#define PIN_ESC	4

#define DDR_DOWN DDRD
#define PORT_DOWN  PORTD
#define PINx_DOWN  PIND
#define PIN_DOWN	6

#define DDR_UP DDRD
#define PORT_UP PORTD
#define PINx_UP  PIND
#define PIN_UP	5

#define DDR_ENTER DDRD
#define PORT_ENTER  PORTD
#define PINx_ENTER  PIND
#define PIN_ENTER 7

#define BUTTONS_PERIOD_CHECK 30
#define BUTTON_PERIOD_REACTION 130


void Buttons_initial (void);
void Int0Ini_interrupt_falling_edge (void);
void Int1Ini_interrupt_falling_edge (void);
void Int1Ini_interrupt_low_level (void);
void Int1Ini_interrupt_rising_edge (void);
void Int1Ini_interrupt_logicChange (void);
// this function gets the exactly which button has been pressed end returns esc down up  or  enter 
void Buttons_qustioning (void);

void button_reaction_Method (ButtonValues sw_button);
bool wait_unpressingY_N (ButtonValues sw_button);
bool buttonAction (ButtonValues sw_button,uint16_t*);
uint16_t longpress_check(ButtonValues sw_button);
void Lock_buttons (void);   // when we go up in sleepmode
ButtonValues PressedButton (void);


#endif /* PUSH_BUTTONS_H_ */