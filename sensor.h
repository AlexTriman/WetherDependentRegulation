
enum Vref
{
	Vinternal,
	VCC
};

#define DDR_ADC DDRA
#define PORT_ADC PORTA
#define OUTSIDE_SENSOR 0 // 
#define FLOW_SENSOR 1  // 
#define QUESTIONING_OF_SENSOR 100  //скільки разів опитувати датчик для отримання середнього значення
#define V_SENSOR 4.1

#define REFERENCE_VOLTAGE 4.1 // напруга завдання для АЦП
#define REFERENCE_RESISTANCE 2950  // опір в омах для опорного резистора, рівний найбільшому значенню опору датчика



float GetADCValue (char, Vref);

float GetAverageADCValue (char, char, Vref);

float ConvertADC_ToResistanceUnits (float, float, float);

float ConvertSensorResistanceToTemperature (float, float, float,  int*);

float GetSensor (char, float);
void sensorErr (float);
