
//*********************************************************************************************
// ФУНКЦІЯ ВИРАХОВУЄ, ЯКОЇ ТЕМПЕРАТУРИ МАЄ БУТИ ГАРЯЧА ВОДА ПОДАЧІ при даній температурі на вулиці
//*********************************************************************************************

// необхідні ввідні:  температура на вулиці
//					  координати точок кривої 
// the_T_outside- температура на вулиці
//   A (the_x1, the_y1)- нижня точка, наприклад ( 20° вулиця - 20° подача)  
//   B (the_x2, the_y2) - верхня точка, наприклад (-20° вулиця - 80° подача)

#include <avr/io.h>
#include "global_varibals.h"
#include "climate.h"
#include "Prog.h"
#include "repeatingHandler.h"




float heating_curve_G = 1.5;  // задана крива погоди
float Kp_G = 40;    // PID Kp
float Ki_G = 1;    // PID Ki
float Kd_G = 2;    // PID Kd

program_t day_prog [7] ={PROG7,PROG2,PROG3,PROG4,PROG1,PROG6,PROG7}; //every day has P1 program in initial conditions

//   on/off for komf periods in minutes
//       
Prog P1 ( 0, 24*60, 0, 0, 0, 0);
Prog P2 (0, 0, 0, 0, 0, 0);
Prog P3 (7*60, 22*60, 0, 0, 0, 0);
Prog P4 (7*60, 8*60, 17*60, 22*60, 0, 0);  
Prog P5 (7*60, 8*60, 17*60, 22*60, 0, 0);
Prog P6 (7*60, 8*60, 12*60, 13*60, 17*60, 22*60);
Prog P7 (0, 24*60, 0, 0, 0, 0);
Prog P8 (0, 24*60, 0, 0, 0, 0);
Prog P9 (0, 24*60, 0, 0, 0, 0);


program_t ChangeProg (int day, program_t* day_prog, char sign)
{
	char num = static_cast<char>(day_prog[day]);
	num += 1*sign;
	if (num>9) num = 1;
	if (num<1) num = 9;
	return static_cast<program_t>(num);
}

char* TextProgNum (int day, program_t* day_prog)  // returns text "P1".."P9" according to current day program
{
	
	switch (day_prog[day])   //
	{
		case PROG1:
		return "p1  ";
		break;
		
		case PROG2:
		return "p2  ";
		break;
		
		case PROG3:
		return "p3  ";
		break;
		
		case PROG4:
		return "p4  ";
		break;
		
		case PROG5:
		return "p5  ";
		break;
		
		case PROG6:
		return "p6  ";
		break;
		
		case PROG7:
		return "p7  ";
		break;
		
		case PROG8:
		return "p8  ";
		break;
		
		case PROG9:
		return "p9  ";
		break;
		
		default:
		return "p1  ";
	}

	return "p1  ";
}

float GetRoomTemp (long int day, float t_comf, float t_eco)
{
	
	switch (day_prog[day-1])   // 0 index refer to MON, 1 to TU, etc
	{
		case PROG1:  
		return P1.SetRoomTempr(t_comf, t_eco);
		break;
		
		case PROG2:  
		return P2.SetRoomTempr(t_comf, t_eco);
		break;
		
		case PROG3:  
		return P3.SetRoomTempr(t_comf, t_eco);
		break;
		
		case PROG4:  
		return P4.SetRoomTempr(t_comf, t_eco);
		break;
		
		case PROG5:  
		return P5.SetRoomTempr(t_comf, t_eco);
		break;
		
		case PROG6:  
		return P6.SetRoomTempr(t_comf, t_eco);
		break;
	
		case PROG7:  
		return P7.SetRoomTempr(t_comf, t_eco);
		break;
		
		case PROG8:  
		return P8.SetRoomTempr(t_comf, t_eco);
		break;
		
		case PROG9:  
		return P9.SetRoomTempr(t_comf, t_eco);
		break;
		
		default:
		return P1.SetRoomTempr(t_comf, t_eco);
	}
	
}


 float GetFlowTemperatureFromCurve (float the_T_outside, float the_heating_curve, float the_room_t, float tflow_max, float tflow_min)       
{
	float m = -the_heating_curve;
	float b = the_room_t+30;
	float x = the_T_outside;
	
	
	float y = m*x+b;
	if (y>tflow_max) y=tflow_max;
	if (y<tflow_min) y=tflow_min;
	if (sens_err_G) y=tflow_max;
	
	return y;	 	
	
}
	
		
	
	
//*********************************************************************************************
//ПІД РЕГУЛЯТОР
//*********************************************************************************************

/*  ПІД регулятор слід запускати не частіше за час на який реагує давач
*/

// вхідні	
// the_T_flow_setpoin - обчислене значення потрібної температури - задана температура
// the_T_flow_sensor  - реальне виміряне значення подаючої температури
//  the_Kp - коефіцієнт пропорційної складової
// the_Ki - коефіцієнт інтегральної складової
// the_Kd - коефіцієнт диференційної складової


float PID_regulator (float the_T_flow_setpoin,  float the_T_flow_sensor, float the_Kp, float the_Ki, float the_Kd)
{
	static float T_flow_sensor_previous = 20;     // реальне виміряне значення темп. подаючої води В ПОПЕРЕДНІЙ ітерації. Перше значення приймаємо 20
	static float mismatch_sum = 0; //сума розузгоджень 
	float mismatch_dif =  the_T_flow_sensor - T_flow_sensor_previous ;  //похибка диференційна
	float mismatch = the_T_flow_setpoin - the_T_flow_sensor ;		// розузгодження
	mismatch_sum += mismatch;
	
	float y = the_Kp/100 * mismatch + the_Ki/100*mismatch_sum  - the_Kd/100 * mismatch_dif;      //  - під розрахунок
	
	if (y>100)              // обмеження границь під регулювання
	{
		y = 100;
	}
	if (y<-100)
	{
		y = -100;
	}
	
	T_flow_sensor_previous = the_T_flow_sensor ;
	
	return y;
}




//************************************************************************************
//ФУНКЦІЯ зупинка сервоприводу (знімає керуючі сигнали до сервоприводу)
//*************************************************************************************









void StopServo (void)
{
		PORT_SERVO_OPEN &= ~(1<<PIN_OPEN);  // вивід нуль на пін відкривання
		PORT_SERVO_CLOSE  &= ~(1<<PIN_CLOSE);    // виводимо 0 на ніжку закривання
		DDR_SERVO_OPEN |=  1<<PIN_OPEN;  // перестраховуємось що ніжка  "відкрити" налаштована як вихід
		DDR_SERVO_CLOSE |=  1<<PIN_CLOSE;  //  аналогічно
		
}


//*********************************************************************************************
// ФУНКЦІЯ КЕРУЄ СЕРВОПРИВОДОМ 
//*********************************************************************************************


/* функцію слід запускати лише після ПІДрегулятора. 
Функція подає сигнали "відкривання" або "закривання" на відповідні ножки мікросхеми залежно від сигналу під-регулятора 
і повертає тривалість імпульсу. Зупинку подавання сигналів на сервопривід потрібно передбачити окремо, коли спливає час імпульсу
інакше сигнал буде йти постійно 
// Вхідні
// ножка мікросхеми для "відкрити"
// ножка мікросхеми для "закрити"
// значення під регулятора  the_PID_signal
// час повного ходу сервоприводу the_servo_period в мілісекундах
 
 // Ці параметри можна змінювати:
*/ 

void openServo(void)
{
	PORT_SERVO_CLOSE  &= ~(1<<PIN_CLOSE);    // виводимо 0 на ніжку закривання    // виводимо -- зупиняємо
	PORT_SERVO_OPEN |=  (1<<PIN_OPEN);    // виводимо сигнал на "відкривання"
	DDR_SERVO_OPEN |=  (1<<PIN_OPEN);  // перестраховуємось що ніжка  "відкрити" налаштована як вихід
}

void closeServo(void)
{
	PORT_SERVO_OPEN &= ~(1<<PIN_OPEN);  // вивід нуль на пін відкривання	    //     виводимо 0 -- зупиняємо
	PORT_SERVO_CLOSE |=  (1<<PIN_CLOSE);  // подаємо сигнал на "закривання"
	DDR_SERVO_OPEN |=  (1<<PIN_OPEN);  // перестраховуємось що ніжка  "відкрити" налаштована як вихід
}

float ServoControl  (float the_PID_signal, float the_servo_period)
{
	float D;   // тривалість імпульса
	
	static float previous_D;  // сюди записується тривалість імпулсу, якщо вона попала в зону нечутливості,
									//	щоб наступного разу додати її до заново порахованої
	D =  previous_D + the_servo_period*(the_PID_signal/100)  ;   //формула вираховуємо тривалість імпульсу 
																							//	+ попередній інтервал якщо він попадав
																							// в зону нечутливості			
	if (D == 0 )  // якщо сигнал під-регулятора дор. 0, то зупиняємо сервопривід
	{		
		StopServo(); 
		return 0;  //тривалість імпульсу = 0
	}	

	if  (D > 0)   // якщо від ПІД-регулятора отримана команда "відкривати"
	{	
		//спочатку перестраховуємось -- зупиняємо сигнал "закривання"
				
		if  (  D >= INSENSITIVE_ZONE  )   // перевіряємо якщо тривалість імпульсу не попадає в зону нечутливості, тоді вивід
		{				
			previous_D = 0; // обнулюємо 	    
			openServo();
			return D;   //виходимо з функції, передаємо тривалість "відкривання"
		}
		else  // якщо тривалість імпульсу потрапляє в зону нечутливості сервоприводу то запамятати значення до наступного виклику функції
		{
			previous_D = D;   // запамятати вирахований інтервал імпульсу для сумування наступного разу
			StopServo();   // вивід нуль на пін відкривання	 //  зупиняємо "відкривання"
			return 0;  //тривалість імпульсу = 0
		}
	}
	else  // сигнал на "закривання"
	{
		 // Спочатку перестраховуємось що "відкривання" зупинене
		
		
		if  (-1*D > INSENSITIVE_ZONE)   // перевіряємо, якщо тривалість імпульсу не попадає в зону нечутливості, тоді вивід
		{															// -1 -- щоб отримати абс значення			
			previous_D = 0; // входу в інтервал нечутливості немає
			return -1*D;   //виходимо з функції, передаємо тривалість "закривання" (його абсолютне значення) 		
		}
		else  // якщо тривалість імпульсу потрапляє в зону нечутливості сервоприводу
		{
			previous_D = D;  // запамятати вирахований інтервал імпульсу для сумування наступного разу
			StopServo();     // виводимо 0 на ніжку закривання    //  зупиняємо "закривання" 
			return 0;  //тривалість імпульсу = 0
		}
	}
}

repeatingHandler servo;

void InterruptingServo (float imp_duration)
{
	static uint16_t imp = 0;
	if (imp_duration == 0) 
	{
		StopServo();
		return;
	}
		
	if (static_cast<uint16_t>(imp_duration) != imp)  //if impuls duration has changed - begin count down again
	{
		servo.perform=false;  //repeat from the begin
		imp = imp_duration;
	}
	if(servo.repeat(imp))
	{
		StopServo();
	}
}

void servoSummer(uint16_t*pid_period_ptr, float* imp_servo_ptr )
{
	
	*pid_period_ptr=0;  //turn off pid calculations
	
	if (  (our_time[DAYOFWEEK]==2 || our_time[DAYOFWEEK]==5)
	              &&
	      our_time[HOURE]==8 
		          &&
	      (our_time[MINUTES]<10)  )	
	{
		*imp_servo_ptr = ServoControl(100,servo_period_G);  
	}	 //open for 10minutes
	else
	{
		*imp_servo_ptr = ServoControl(-100,servo_period_G);   //signal to servo to close		
	}
	
}

void seasonSummer (void)
{
	servoSummer(&PIDperiod_G, &impulse_for_servo_G);	
}

void seasonWinter(uint16_t *pid_period_ptr)
{
	*pid_period_ptr = PID_PERIOD;
}

void checkSummerWinter(float t_out, float t_change_season)
{
	if (t_out>=t_change_season) seasonSummer();
	else seasonWinter(&PIDperiod_G);
	
}