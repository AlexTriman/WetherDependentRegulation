






//*********************************************************************************************
// ФУНКЦІЯ ІНІЦІЮЄ ТАЙМЕР0 8біт  в Atmega 8
//*********************************************************************************************
 




// 
/*
void Timer0Initiation (int the_period_ms, bool the_do_interrupt)
{

	

	
	if (the_period_ms =0) the_period_ms= 1 ; // (захист від чайника)
	if (the_do_interrupt)  TIMSK = 1 << TOIE0;  // ініціювати переривання, якщо вимагається

		//TCCR0 = 1 << WGM01;  // Mode = CTC
	//налаштовуємо дільник частоти для таймера
	
    
	short int prescalor [4]  {1024, 256, 64, 8};
	char i = 0;
	char ticks;
	
	
	ticks =the_period_ms*(FCPU/1000)/prescalor[0] +0.5  // формула виведена  (the_period/1000)*FCPU/1024  // + 0.5 для заокруглення
	
	for 
		ticks =the_period_ms*(FCPU/1000)/prescalor[i] +0.5  // формула виведена  (the_period/1000)*FCPU/1024  // + 0.5 для заокруглення
 		i++;   // на наступному циклі використати наступний 
	
	if (ticks 255))
	
	
	
	
	if  ( !(ticks <=255)) // якщо кількість кроків не є меншою 255, то вибираємо менший дільник, щоб збільшити частоту годинника таймера
	{
		
	}
	else
	{
		OCR0 = ticks; 
	}
		TCCR0 = (0<<CS02)|(1<<CS01)|(0<<CS00)   // 1000 000/8,  seconds per tick
	    
		// 0.001024*244 ~= .25 SIG_OUTPUT_COMPARE0A will be triggered 4 times per second.
	
} */



//*****************************************************************************
// ФУНКЦІЯ ініціалізація таймера2 16МГц, виклик переривань кожну 1мс. 
// Увага!  частота процесора рівня 16МГц  Якщо інакша потрібно змінювати OCR2 = 250 (регістр порівняння); 
//
//*****************************************************************************
/*
What I like to do often is have one of the timers interrupt the processor on a regular basis so I can keep track of time.
 Counter 1 and 2 are perfect for the job because we can use the OCRx registers to control the interval.
 If we leave timer1 for the motors we can make use of timer2.
 We could use timer0 but it's lack of a compare unit means we have to resort to stupid software tricks or hardware compromises to give us 
 a reasonable timer resolution.

Say we want to keep millisecond time. That is, interrupt the processor once every millisecond so we can poll something or update system time.
 What we will do is change the timer so that instead of starting over at zero when it reaches 255 it will start over 
 when it reaches something we put into OCR2. Between the timer2 clock prescales (which have more choices than timer0) and OCR2 
 we can pretty much set up any timer resolution we like.

First, the prescale. We need to choose one that that will result in a timer frequency that when again divided by a number from 0 to 255 will result in
 a frequency that we want. For a 16 MHz clock 64 is a good choice. That gives us 250000. Divide that by 250 and we get 1000. Bingo. Here we go:

TCCR2 = _BV(WGM21)    // CTC mode, TOP is OCR2
     || _BV(CS22)     // prescale of 64
TIMSK |= _BV(OCIE2);  // enable compare match interrupt
OCR2 = 250;
sei();
Now, all you need is an interrupt handler for SIG_OUTPUT_COMPARE2. This just toggles the PB3 pin.
*/
//When we use a timer like this we have to be careful of the frequency we choose.
// Because an interrupt forces the processor to drop whatever it is doing to handle it we don't want to do it too often. 
// Otherwise the processor won't get anything done! With a 16 MHz clock
// and an interrupt happening every 1/1000 of a second the processor can do about 16000 other instructions in between. That's ok. 
//


	
#include <avr/io.h>
#include <avr/interrupt.h>
#include "global_varibals.h"
#include "Timing.h"

//#define FCPU 4000000u




long int our_time[7] {0, 0, 0, 1, 24, 3, 2015};       //  тут записуємо час від мс до року відлік від 1го січня 2015
/*
void Atmega8Timer2Ini (void)
{
sei();   // ініціалізація переривань
TIMSK |= (1 << OCIE2); // enable compare match interrupt
TCCR2 |= (1 << WGM21);  // CTC mode, TOP is OCR2 
TCCR2 |= (1 << CS22)|(1 << CS21);     // prescale of 256  8 000 000 / 256 = 31250 -> частота годинника
  
OCR2 = 250;					// compare with this // дозволяє робити перехід при досягненні верхнього значення  31250/250=125
							// при досягненні 250 отримуємо частоту 125 раз на секунду тобто 1/125=0,008с кожні 8 мс буде переривання
}

// Вставити у головній програмі
ISR (TIMER2_COMP_vect)  
{
	 // тут викликати програму годинника ClockTick ()
}
*/




void Atmega16Timer16bitIni (void)
{
	
	TCCR1B |= (0<<CS12)|(1<<CS11)|(1<<CS10);  // // prescale of 64  4000000 / 64 = 62500 -> частота годинника
												
	
	
	unsigned int r = 250;  //  we need every interrupt. 62500/1000 62.5per 1ms  62.5*4=250    4ms   
	unsigned int rl =  r & 0x00ff;
	unsigned int rh =  (r & 0xff00)>>8;
	
    TCCR1B |=(1<<WGM12); //regime cct
	OCR1AH = rh;
	OCR1AL = rl;
	TIMSK |= (1<<OCIE1A );  // Когда этот бит установлен в 1 и разрешены прерывания,
	// процессор реагирует вызовом прерывания по вектору $00C (OC1Aaddr)
	// на событие совпадения счёта с константой в регистре OCR1A.
	sei();   // ініціалізація переривань
	
}
	
// *****************************************************************************************
//ФУНКЦІЯ ГОДИННИК  
//***************************************************************************************
// В  головній програмі має бути створена глобальна змінна-масив
// int our_time [7] {MILISECONDS, SECONDS, MINUTES, HOURE, DAY, MONTH, YEAR}  - глобальна змінна-масив, в яку запсується дані про час
//  
//   

// вхідні дані час з якого робити відлік
 
void ClockTick (void)
{
		
	our_time[SECONDS]++; 
			
	if  (our_time[SECONDS]>=60)
		{
			our_time[SECONDS] = 0;
			our_time[MINUTES]++;
		}
	else  return; 
	
	if (our_time[MINUTES] >=60)  // чи натікало 60хв
		{
			our_time[MINUTES] = 0;
			our_time[HOURE]++;
		}
	else return; 
		
// обробка днів
	if (our_time[HOURE] >= 24)   // чи натікало 24 години
		{
			our_time[HOURE] = 0;   // обнулити години
			our_time[WEEKDAY]++;   // day of the week ++
			our_time[DAY]++;        // на один день збільшити 
			
		}
	else  return; 
	
	if (our_time[WEEKDAY]>7) our_time[WEEKDAY]=1;
						
 // обробка місяця Лютого						
	if (  (our_time[DAY] == 29)  && (our_time[MONTH] == 2) && (our_time[YEAR]%4 != 0) )   // якщо минуло 28 днів і це місяць лютий а рік не високосний
		{
			our_time[DAY] = 1;
			our_time[MONTH] = 3;    // настав місяць березень
			return;     
		}
						
													
	if ( (our_time[DAY] == 30) && (our_time[MONTH] == 2) )    //у високосний рік, якщо 29 днів минуло
		{
			our_time[DAY] = 1;
			our_time[MONTH] = 3;    // настав місяць березень
			return;
		}
	// обробка місяців в яких 30 днів
	if ( (our_time[DAY] == 31)  &&  (  (our_time[MONTH]==4) || 
																 (our_time[MONTH]==6) ||
																 (our_time[MONTH]==9) ||		
																 (our_time[MONTH]==11)																		 
									)
	   )					
		{
			our_time[DAY] = 1;
			our_time[MONTH]++;  // наступний місяць  
			return;  // зміни року після цього блоку не відбуватиметься
		}
	  //  обробка місяців, у яких 31 день
	if (our_time[DAY] >=32) 
		{
			our_time[DAY] = 1;
			our_time[MONTH]++; 
		}
	// обробка років
	if  (our_time[MONTH] >=13 )
		{
			our_time[MONTH] = 1;
			our_time[YEAR] ++;
		}
}





