/*
 * global_varibals.h
 *
 * Created: 19.07.2015 22:26:22
 *  Author: notebook
 */ 


#ifndef GLOBAL_VARIBALS_H_
#define GLOBAL_VARIBALS_H_


# define F_CPU 4000000
#include <stdint.h>
// time programs


#define SECONDS 0
#define MINUTES 1
#define HOURE 2
#define WEEKDAY 3
#define DAY 4
#define MONTH 5
#define YEAR 6

// we can change comf/eco 5 times per day,  we define in minutes from the begining 00:00



enum program_t
{
	PROG1,
	PROG2,
	PROG3,
	PROG4,
	PROG5,
	PROG6,
	PROG7,
	PROG8,
	PROG9
	
};

enum DisplayOption
{
	SHOW_PARAMETER,
	SHOW_TEXT,
	EDIT_PARAMETER
	
};


enum Parameter //this is the list of all parameters that can be edited
{
	NONE,
	T_KOMF,
	T_KOMF_,	
	T_ECO,
	T_ECO_,
	T_OUTSIDE,
	T_FLOW,
	T_SET,
	PROG,
	MENU,
	MO,
	TU,
	WE,
	TH,
	FR,
	SA,
	SU,
	MO_P,
	TU_P,
	WE_P,
	TH_P,
	FR_P,
	SA_P,
	SU_P,		
	CURVE,
//	SERVO,
	P,
	I,
	D,
	TIME,
	DAYOFWEEK,
	CURVE_,
	SERVO_,
	P_,
	I_,
	D_,
	TIME_,
	DAYOFWEEK_,
	RESERVE	
};

enum ButtonValues
{
	
	DOWN,
	UP,
	ENTER,
	UNPRESSED,
	PRESSED,
	ESC
};

enum led_num
{
	TCOMF_LED,
	TECO_LED,
	TFLOW_LED,
	TSET_LED,
	TOUTSIDE_LED,
	PROG_LED,
	MENU_LED,
	MO_LED,
	TU_LED,
	WE_LED,
	TH_LED,
	FR_LED,
	SA_LED,
	SU_LED
	
};

#include <avr/interrupt.h>
#include <avr/delay.h>
#include "digitsdisplay.h"

#include "repeatingHandler.h"

#include "leds.h"
#include "push_buttons.h"
#include "sounder.h"
#include "menu.h"
#include "Timing.h"
#include "RTC.h"
#include "sleeping.h"

#define PID_PERIOD 3000;

extern bool tick_G;
extern long int our_time[7]; //{0, 0, 0, 0, 1,1,2015};       //  тут записуємо час від мс до року відлік від 1го січня 2015

extern float t_outside_G;                 //  зовнішня температура


extern float t_flow_G;						// температура води подачі
extern float t_flow_setpoint_G;          // вираховане значення температури подачі
extern float impulse_for_servo_G;     // тривалість імпульсу для сервоприводу
extern float t_room_comfortable_G; //температура комфортна задана
extern float t_room_eco_G; 			// нічна температура
//float our_curve_koef;    // номер кривої
extern float tflow_max_G;     //  максимальна температура подачі
extern float servo_period_G;  //  час повного ходу періоду
extern float Kp_G;    // PID Kp
extern float Ki_G;    // PID Ki
extern float Kd_G;    // PID Kd
extern float heating_curve_G;  // задана крива погоди
extern float our_room_t_correction;
extern uint16_t PIDperiod_G;
extern menuItem *selectedMenuItem;
extern unsigned int counts_G;
extern ButtonValues button_G; //the button has been pressed
extern led_num chosen_led_G;    // RenewScreen uses to specify what led to chose regarding to the menu item 
extern program_t day_prog [7]; //every day has P1 program in inititial conditions
extern repeatingHandler blickOn;
extern repeatingHandler blickOff;
extern repeatingHandler servo;
extern repeatingHandler longpressWait;
extern repeatingHandler longpressRepeats;
extern repeatingHandler switches_ask;
extern repeatingHandler debouncing;
extern repeatingHandler sw_button_action;
extern repeatingHandler checkSeason;  //repeat checking the season change from winter to summer and viceversa
extern bool sens_err_G;
void Total_ini (void);


#endif /* GLOBAL_VARIBALS_H_ */

