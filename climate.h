/*
 * climate.h
 *
 * Created: 04.12.2015 16:10:08
 *  Author: Alex
 */ 


#ifndef CLIMATE_H_
#define CLIMATE_H_

# define INSENSITIVE_ZONE 1000  // зона нечутливості в мілісекундах
# define DDR_SERVO_OPEN DDRA   // тут задаємо який пін якого порта буде "відкриванням"  для конфігурування
# define DDR_SERVO_CLOSE DDRA   //  щоб потім налаштувати DDRB
# define PORT_SERVO_OPEN PORTA  //  тут який порт для відкривання
# define PORT_SERVO_CLOSE PORTA  //  тут задаємо який пін якого порта буде "закривання" щоб виводити
#define PIN_OPEN 6              // пін для відкривання
#define PIN_CLOSE 7              // пін для відкривання

float GetRoomTemp (long int, float, float);
float GetFlowTemperatureFromCurve (float, float, float, float, float);
float PID_regulator (float, float, float, float, float);
void StopServo (void);
float ServoControl  (float, float);
void InterruptingServo (float);
char* TextProgNum (int day_of_week, program_t* day_prog);
program_t ChangeProg (int day, program_t* day_prog, char sign);
void checkSummerWinter(float t_out, float t_change_season);

#endif /* CLIMATE_H_ */