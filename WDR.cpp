/*
 * WatherDependControler.cpp
 *
 * Created: 20.06.2015 13:36:05
 *  Author: notebook
 запуск програми в режимі без виведення на екран
 - файл climate - обчислення по графіку
 - файл sensor - опитування датчиків
 - файл timing - годинник, використовується для запуску з періодами
 - файл global_varibals - для глобальних змінних
 
 
 */ 





#include <avr/io.h>
#include <avr/interrupt.h>
//#include <math.h>
// для зручності: у змінній-масиві вводити не індекс а слова

# define DDR_SERVO_OPEN DDRA   // тут задаємо який пін якого порта буде "відкриванням"  для конфігурування
# define DDR_SERVO_CLOSE DDRA   //  щоб потім налаштувати DDRB
# define PORT_SERVO_OPEN PORTA  //  тут який порт для відкривання
# define PORT_SERVO_CLOSE PORTA  //  тут задаємо який пін якого порта буде "закривання" щоб виводити
#define PIN_OPEN 6              // пін для відкривання
#define PIN_CLOSE 7              // пін для закривання



#include "global_varibals.h"
#include "Timing.h"
#include "repeatingHandler.h"
#include "climate.h"
#include "sensor.h"
#include "digitsdisplay.h"
#include "menu.h"
#include "leds.h"
#include "Prog.h"
#include "push_buttons.h"
#include "sounder.h"


// Задаємо на яких ножках розміщені сенсори

float t_outside_G = 0;                 //  зовнішня температура 
float t_outsidecor_G=0;
float t_outS_W=17;
float t_flow_G = 60;						// температура води подачі
float t_flowcor_G=0;
float t_flow_setpoint_G = 50;          // вираховане значення температури подачі
float tflow_max_G = 85;
float tflow_min_G = 30;
float impulse_for_servo_G = 0 ;     // тривалість імпульсу для сервоприводу
float t_room_comfortable_G = 20; //температура комфортна задана
float t_room_eco_G = 17; 			// нічна температура
float servo_period_G = 60000;  //  час повного ходу періоду в мс
uint16_t PIDperiod_G =PID_PERIOD;
ButtonValues button_G = UNPRESSED;  //

repeatingHandler t_flow;
repeatingHandler PID;
repeatingHandler displayRenew;
repeatingHandler leds;
repeatingHandler switches_ask;
repeatingHandler t_out;
repeatingHandler checkSeason;

int main (void)
{
	
    Total_ini();
			
	while (1)
	{
		// DOING WITH BUTTONS
		Buttons_qustioning();					
	
		//DOING WHITH POWER IF LESS THEN 1.5v IT POINTS THAt WE SHODE POWER SAVE MODE
		sleeping ();
		  
	 	// GET THE OUTSIDE TEMPERATURE        
	   if (t_out.repeat(2500)) // опитувати давач зовн. температури кожну 2.5с . 
		{
			t_outside_G = GetSensor(OUTSIDE_SENSOR,t_outsidecor_G);					
			sensorErr (t_flow_G);
		} 
		
		// GET THE FLOW TEMPERATURE
        if (t_flow.repeat(1500)) // опитувати давач зовн. температури кожну 1,5 с . 
		{
			
			t_flow_G = GetSensor(FLOW_SENSOR,t_flowcor_G);
			sensorErr (t_flow_G); 
		}
		
		
		// CALCULATE SIGNAL DURATION FOR SERVO AND RUN THE SERVO
        if (PID.repeat(PIDperiod_G)) // робимо розрахунок кожні с . 
		{
			//calculate a temperature correction regarding to week program 
			float t_room = GetRoomTemp (our_time[WEEKDAY], t_room_comfortable_G, t_room_eco_G);
			
			// розрахунок уставки температури подачі			
			t_flow_setpoint_G = GetFlowTemperatureFromCurve (t_outside_G, heating_curve_G, t_room, tflow_max_G, tflow_min_G);
			
			//вирахувати ПІД сигнал
			float PID_signal = PID_regulator (t_flow_setpoint_G,  t_flow_G, Kp_G, Ki_G, Kd_G);
			
			//Керуючі сигнали на сервопривід
			impulse_for_servo_G = ServoControl  (PID_signal, servo_period_G);			
		} 
		
		
		// HERE WE CONTROL THE SERVO TO STOP IN TIME
		InterruptingServo (impulse_for_servo_G);
		
		//DISPLAY
		
		if (displayRenew.repeat(5000))
		{
		  RenewScreen();						
		}
				//
		// DOING WITH LEDS
		if (leds.repeat(120))
		{			
			LightUpLed(chosen_led_G);			
		}		

		//Checking out the season change
		if (checkSeason.repeat(12000))
		{
			checkSummerWinter(t_outside_G, t_outS_W);
		}
	}	
}



#define TICKS_ms 4
// 	переривання для таймера1 16bit
ISR ( TIMER1_COMPA_vect)   //every 4ms
{		
	t_out.ticks+=TICKS_ms;
	switches_ask.ticks+=TICKS_ms;  
    t_flow.ticks+=TICKS_ms;
    PID.ticks+=TICKS_ms;
    blickOn.ticks+=TICKS_ms;
    blickOff.ticks+=TICKS_ms;
    displayRenew.ticks+=TICKS_ms;
	leds.ticks+=TICKS_ms;
	servo.ticks+=TICKS_ms;
	sw_button_action.ticks+=TICKS_ms;
	
	if (blick_screen_G) IND_Upd_bliks();// if the flag "blick_screen" is on    
	else IND_Update(); 	 // update display		
	
}


// the interrupt for the buttons

ISR (INT1_vect)
{	
	//GICR &= ~(1 << INT1);  		
	//button_G = PRESSED;		
}


ISR (TIMER2_OVF_vect)
{
	ClockTick ();
}