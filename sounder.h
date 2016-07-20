/*
 * sounder.h
 *
 * Created: 22.02.2016 13:57:05
 *  Author: Alex
 */ 



#ifndef SOUNDER_H_
#define SOUNDER_H_

#define SOUNDER_DDR DDRA
#define SOUNDER_PORT PORTA
#define SOUNDER_PIN 5

void Sounder_port_ini (void);
void Beep (void);

#endif /* SOUNDER_H_ */