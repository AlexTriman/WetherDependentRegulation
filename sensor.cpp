 //*********************************************************************************************
// ФУНКЦІЯ, ЯКА ПОВЕРТАЄ ЗНЧЕННЯ ДАВАЧА. ЦЕ ЗНАЧЕННЯ Є УСЕРЕДНЕНЕ
//*********************************************************************************************


// функія розміщується у циклі main,

// у параметрах задається кількість опитувань давача для отримання середнього значення
// за один виклик функції робиться тільки одне опитування давача
// ????функція повертає "нічого" доти поики не отримає  середнє значення 

// Вхідні дані для функції
//   номер входу давача
//	 кількість виміряних значень перед усередненням
#include <avr/io.h>
#include <util/delay.h>
#include "global_varibals.h"
#include "sensor.h"
#include "digitsdisplay.h"
#include <math.h>


//**********************************************************************************************
//***Функція отримує значення АЦП для заданої ніжки контролера (ДЛЯ atmega8 це ніжки з порту С)*****
//***********************************************************************************************
// повністю настроює ацп під себе
//  ця функція перезапустить ацп по новому навіть, якщо він якимось чином був запущений раніше,
//  одноразово опитує давач і виключає ацп повністю,
// функція не запускає переривань для ацп
  



float GetADCValue (char the_pin, Vref V_ref)
{
	ADCSRA |= (0<<ADEN);		// Виключаємо ацп, запобігання: якщо якимось чином ацп було викликано іншими функціями.
	ADMUX  &= 0b11110000;   // Скинути налаштування каналу ADC, default adc0:  MUX3=0  MUX2=0 MUX1=0 MUX0=0  
	switch (the_pin)  // заданий пін встановлюємо як вхід
	{
		
		
		case 0:
		DDR_ADC &=  ~(1<<PORTA0); //  MUX3= 0  MUX2= 0 MUX1= 0 MUX0= 0   (adc0)
		PORT_ADC &= ~(1<<PORTA0);
		break;
		
		case 1:
		DDR_ADC &=  ~(1<<PORTA1);
		PORT_ADC &= ~(1<<PORTA1);			
		ADMUX  |= (1<<MUX0);	//  MUX3= 0  MUX2= 0 MUX1= 0 MUX0= 1   (adc1)
		break; 
		
		case 2:
		DDR_ADC &=  ~(1<<PORTA2);
		PORT_ADC &= ~(1<<PORTA2);
		ADMUX  |= (1<<MUX1);  //  MUX3= 0  MUX2= 0 MUX1= 1 MUX0= 0   (adc2)
		break;
		
		case 3:
		DDR_ADC &=  ~(1<<PORTA3);
		PORT_ADC &= ~(1<<PORTA3);
		ADMUX  |= (1<<MUX1)|(1<<MUX0); //  MUX3= 0  MUX2= 0 MUX1= 1 MUX0= 1   (adc3)
		break;
		
		case 4:
		DDR_ADC &=  ~(1<<PORTA4);
		PORT_ADC &= ~(1<<PORTA4);
		ADMUX  |= (1<<MUX2); //  MUX3= 0  MUX2= 1 MUX1= 0 MUX0= 0   (adc4)
		break;
		
		case 5:
		DDR_ADC &=  ~(1<<PORTA5);
		PORT_ADC &= ~(1<<PORTA5);
		ADMUX  |= (1<<MUX2)|(1<<MUX0); //  MUX3= 0  MUX2= 1 MUX1= 0 MUX0= 1   (adc5)
		break;	
		
		}
	// Налаштовуємо АЦП
	
	ADMUX  |= (1<<ADLAR); // Вибираємо ліве розміщення значення АЦП (8біт без двох перших розрядів, без них похибка незначна)
	
	ADCSRA |= (1<<ADPS2)|(1<<ADPS0);  //Встановлюємо prescalor рівним 16 (біти ADPS2 =1, ADPS1 = 0, ADPS0 = 0)
	ADCSRA &= ~(1<<ADPS1);
	// таким чином маємо частоту розбиття 1 000 000/16 = 62 500 Гц або 62.5кГц
	// це тільки для безперервного режиму
	
	switch (V_ref)
	{
		case Vinternal:
			ADMUX |= (1<<REFS0)|(1<<REFS1);  // Встановлюємо, що максимальне значення АЦП рівне напрузі  V=2.56В (REFS1=0),
			break;
		case VCC:
			ADMUX &= ~(1<<REFS1); // Встановлюємо, що максимальне значення АЦП рівне напрузі на АREF VCC (REFS1=0),
			ADMUX &= ~(1<<REFS0);
			break;
		//default: 
			//ADMUX &= ~(1<<REFS1);     // AVCC with external capacitor at AREF pin
			//ADMUX |= (1<<REFS0);  
		
	}
		
	ADCSRA |= (1<<ADEN);    //Включаємо АЦП
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	
	while(ADCSRA & (1 << ADSC));   //  this line waits for the ADC to finish
	
	// отримати значення з АЦП
	long int ADC_value_L = ADCL;
	ADC_value_L = ADC_value_L >> 6;
	long int ADC_value_H = ADCH;
	ADC_value_H =  ADC_value_H << 2;
	long int ADC_value = ADC_value_L|ADC_value_H;
	
	return ADC_value;
}




//**********************************************************************************************
//***Функція отримує середнє значення АЦП
//***для заданої ніжки контролера та кількості опитувань датчика
//**********************************************************************************************
// the_pin - ніжка, на якій давач
// the_range- скільки значень виміряти, щоб вирухвати середнє

float GetAverageADCValue (char the_pin, char the_range, Vref V_ref)
{
	
	float ADC_value_Sum = 0; // змінна, яка використовується для сумуваня значень ацп
	
	for (int i=0;i<the_range;i++)
	{
		ADC_value_Sum += GetADCValue(the_pin, V_ref);    // при кожній операції розрахунку ацп сумувати значення
	}
	
	float y =  static_cast<float>(ADC_value_Sum)/static_cast<float>(the_range); // конвертація у флоат тип, щоб результат був флоат
	
	return y;
		
}






//*********************************************************************************************
// ФУНКЦІЯ, ЯКА КОНВЕРТУЄ АЦП ЗНАЧЕННЯ У ОПІР ДАТЧИКА.
//*********************************************************************************************


// Датчик омічний підєднується до дільника напруги (одного резистора, опір якого рівний найбільшому значенню опору датчика)  
// 
// Вхідні: значення ацп яке треба конвертувати
//         вказати опорну напругу
//         опір резистора дільника



float ConvertADC_ToResistanceUnits (float the_adc_value, float the_refV, float the_refR, float V )
{
	float R_sensor;   
	R_sensor = V*1024*the_refR/the_adc_value/the_refV-the_refR;  // формула виведена 
	return R_sensor;   
}



//*********************************************************************************************
// ФУНКЦІЯ: КОНВЕРТУЄ ЗНАЧЕННЯ ОПОРУ В ЗНАЧЕННЯ ТЕМПЕРАТУРИ ЗГІДНО ЗАДАНОЇ МАТРИЦІ ДАТЧИКА
//*********************************************************************************************
// Вхідні дані:  

#define  HEIGHT 12  // висота матриці датчика 

// Вхідні параметри: the_sensor_resistance - опір датчика 
//					 the_sensor_matrix     - матриця - характеристика датчика  опір-температура


// матриця датчика температура - відповідний опір
  
// int *ptr_the_sensor_matrix вказівник на двовимірну матрицю
										//     y(градуси цельсія)    x(опір ом)

//Дата датчика
float our_sensorDeg[HEIGHT] =   {-20, -10, 0,   10,  20,  30,  40,  50,  60,  70,  80,  90};
float our_sensorRes [HEIGHT]   = {1372,1495,1630,1772,1922,2080,2245,2417,2597,2785,2980,3182};


int SegmentOnCurve (float the_sensorR, float *ptr_the_sensorRes, int h) {
	
	int k; // в цю змінну запишемо номер проміжку куди потрапить опір датчика
	
	if (the_sensorR<ptr_the_sensorRes[0]) {
		k = 0;
		return k;
	}
	
	if (the_sensorR>=ptr_the_sensorRes[h-1]) {
		k = h-2;
		return k;
	}
	
	for (int i=0; i<=h-2; i++) {
		if ( (the_sensorR >= ptr_the_sensorRes[i]) && (the_sensorR<ptr_the_sensorRes[i+1]) )	 {
			k=i;   //записати в змінну k номер проміжку
			
			return k;
		}
	}
	return 0;
}

float YfromXLine (float x1, float y1, float x2, float y2, float x) {
	// перевірка на ділення на нулль
	if (x2==x1) {
		return tflow_max_G;  // крива задана невірно, задати 50 град темп.
	}
	float m = (y2 - y1)/(x2-x1);
	float y = m* (x - x1) + y1;
	
	return y;
}

float ConvertSensorResistanceToTemperature (float the_sensorR, float *ptr_the_sensorRes, float *ptr_the_sensorDeg, int h)
{
	
	int k = SegmentOnCurve(the_sensorR, ptr_the_sensorRes,HEIGHT);
	
	float y = YfromXLine(ptr_the_sensorRes[k],ptr_the_sensorDeg[k],ptr_the_sensorRes[k+1],ptr_the_sensorDeg[k+1], the_sensorR);
	return y;
}


float GetSensor (char the_pin, float correction)
 {			
			// вкладені функції
	float adc_value;
	float sensor_resistance;
	float temperature;
	
	// ініціалізація одновимірного масиву вказівників на масив давача (в стеку)
		
	adc_value = GetAverageADCValue (the_pin, QUESTIONING_OF_SENSOR, VCC);
	sensor_resistance = ConvertADC_ToResistanceUnits (adc_value, REFERENCE_VOLTAGE, REFERENCE_RESISTANCE,V_SENSOR);	
	temperature = ConvertSensorResistanceToTemperature (sensor_resistance, our_sensorRes, our_sensorDeg, HEIGHT);
	return  temperature+correction;
	
	
}



void sensorErr (float sens_value)
{
	if (sens_value>120||sens_value<(-40)) sens_err_G = true;		
	else sens_err_G = false;		
}
