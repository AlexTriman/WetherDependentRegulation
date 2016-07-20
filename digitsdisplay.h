/*
 * digitsdisplay.h
 *
 * Created: 05.09.2015 21:51:09
 *  Author: notebook
 */ 


#ifndef DIGITSDISPLAY_H_
#define DIGITSDISPLAY_H_



#include <avr/io.h>

//**** ��������� ******************************
#define PORT_IND PORTB
#define DDR_IND DDRB

#define PORT_TR PORTC
#define DDR_TR DDRC

#define NUM1 3
#define NUM2 2
#define NUM3 1
#define NUM4 0

#define SEG_A 0
#define SEG_B 1
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5
#define SEG_G 6
#define SEG_DP 7

#define AMOUNT_NUM 4
//when blicking is shosen define durations for ON and OFF
#define BLICKON 500
#define BLICKOFF 400

//��� ����� ����� ��������� ��� ������ ���������
//#define LightOutAll()  PORT_TR |= (1<<NUM1)|(1<<NUM2)|(1<<NUM3)|(1<<NUM4)
#define LightOutAll()  PORT_TR &= ~((1<<NUM1)|(1<<NUM2)|(1<<NUM3)|(1<<NUM4))
//#define BurnDigit(port, digit) port &= ~(1<<digit)  
#define BurnDigit(port, digit) port |= (1<<digit)  
#define ValueBuf() (buf[count])

//����� 7-�� ���������� ����������


extern bool blick_screen_G;
/***********************************************************************************
*   Function name :   IND_Init
*   Returns :         ���
*   Parameters :      ���
*   Purpose :         ������������� ������ �����-������, ������� ������ ����������
************************************************************************************/
void IND_Init(void);
void FullOffIND (void);
/***********************************************************************************
*   Function name :   IND_Output
*   Returns :         ���
*   Parameters :      value - ����� ��� ��������������, comma - ������� ����� �� ����������
*   Purpose :         ����������� 16-�� ��������� �����, ���������� ��� � ����� ����������
***********************************************************************************/
void IND_Output (unsigned int value, unsigned char comma);

/***********************************************************************************
*   Function name :   IND_Update
*   Returns :         ���
*   Parameters :      ���
*   Purpose :         ������� �� ��������� ����� �� ������.
*                     ��� ������� ����� �������� �� ���������� �������
***********************************************************************************/
void IND_OutputSymbol (const char* symbol, unsigned char pos);
void IND_OutputText(const char* text, unsigned char comma);
void IND_OutputInteger(unsigned int value, unsigned char comma);


void IND_Update(void);


#endif /* DIGITSDISPLAY_H_ */

void IND_Upd_bliks (void);
/***********************************************************************************
*   Function name :   IND_Update
*   Returns :         ���
*   Parameters :      ���
*   Purpose :         ������� �� ��������� ����� �� ������ ��� ���� ����� �������.
*                     ��� ������� ����� �������� �� ���������� �������
***********************************************************************************/