/*
 * _4digitdisplay.cpp
 *
 * Created: 05.09.2015 21:44:18
 *  Author: notebook
 */ 

#include "digitsdisplay.h"
#include "repeatingHandler.h"

volatile unsigned char buf[AMOUNT_NUM] = {0, 0, 0, 0};

#define CHARACTER_0 0
#define CHARACTER_o 10
#define CHARACTER_p 11
#define CHARACTER_n 12
#define CHARACTER_d 13
#define CHARACTER_y 14
#define CHARACTER_t 15
#define CHARACTER_e 16
#define CHARACTER_r 17
#define CHARACTER_l 18
#define CHARACTER_i 19
#define CHARACTER_  20
#define CHARACTER_a  21
#define CHARACTER_g  22
#define CHARACTER_s  23
#define CHARACTER_c  24
#define CHARACTER_u  25
#define CHARACTER_minus  26
#define CHARACTER_degree 27

bool blick_screen_G = false;


unsigned char number[] = 
{
  (1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(0<<SEG_G), //0
  (0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G), //1
  (1<<SEG_A)|(1<<SEG_B)|(0<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(0<<SEG_F)|(1<<SEG_G), //2
  (1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(1<<SEG_G), //3   
  (0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G), //4
  (1<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G), //5 
  (1<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G), //6
  (1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G), //7   
  (1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G), //8
  (1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G),  //9    
  
  (0<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(0<<SEG_F)|(1<<SEG_G),  //'o'    10
  (1<<SEG_A)|(1<<SEG_B)|(0<<SEG_C)|(0<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G),  //'p'    11
  (0<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(1<<SEG_E)|(0<<SEG_F)|(1<<SEG_G),  //'n'    12
  (0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(0<<SEG_F)|(1<<SEG_G),  //'d'    13
  (0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G),  //'y'    14
  (0<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G),  //'t'    15
  (1<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G),  //'e'    16
  (0<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(0<<SEG_D)|(1<<SEG_E)|(0<<SEG_F)|(1<<SEG_G),  //'r'    17
  (0<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(0<<SEG_G),  //'l'    18
  (0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G),  //'i'    19
  (0<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G),  //' '    20
  (1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G),  //'a'    21
  (1<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(0<<SEG_G),   //'g'    22
  (1<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G),   //'s'    23
  (1<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(0<<SEG_G),   //'c'    24
  (0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(0<<SEG_G),   //'u'    25
  (0<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(1<<SEG_G),   //'-'    26
  (1<<SEG_A)|(1<<SEG_B)|(0<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)   //'degree'    27
  
};

//************************************************************************
void IND_Init(void)
{
  unsigned char i;
  PORT_IND = 0xff;
  DDR_IND = 0xff;
  
  LightOutAll();
  DDR_TR |= (1<<NUM1)|(1<<NUM2)|(1<<NUM3)|(1<<NUM4);

  for(i = 0; i < AMOUNT_NUM; i++) buf[i] = 0;
}

void IND_OutputSymbol (const char* symbol, unsigned char pos)
{	
		switch (symbol[0])
		{
			case 'o':
			buf[pos-1] = number[CHARACTER_o];
			break;
			case 'p':
			buf[pos-1] = number[CHARACTER_p];
			break;
			case 'n':
			buf[pos-1] = number[CHARACTER_n];
			break;
			case 'd':
			buf[pos-1] = number[CHARACTER_d];
			break;
			case 'y':
			buf[pos-1] = number[CHARACTER_y];
			break;
			case 't':
			buf[pos-1] = number[CHARACTER_t];
			break;
			case 'e':
			buf[pos-1] = number[CHARACTER_e];
			break;
			case 'r':
			buf[pos-1] = number[CHARACTER_r];
			break;
			case 'l':
			buf[pos-1] = number[CHARACTER_l];
			break;
			case 'i':
			buf[pos-1] = number[CHARACTER_i];
			break;
			case 'a':
			buf[pos-1] = number[CHARACTER_a];
			break;
			case 'g':
			buf[pos-1] = number[CHARACTER_g];
			break;
			case 's':
			buf[pos-1] = number[CHARACTER_s];
			break;
			case 'c':
			buf[pos-1] = number[CHARACTER_c];
			break;
			case 'u':
			buf[pos-1] = number[CHARACTER_u];
			break;
			case '-':
			buf[pos-1] = number[CHARACTER_minus];
			break;
			case '*':
			buf[pos-1] = number[CHARACTER_degree];
			break;
			
			case '0':
			buf[pos-1] = number[0];
			break;
			case '1':
			buf[pos-1] = number[1];
			break;
			case '2':
			buf[pos-1] = number[2];
			break;
			case '3':
			buf[pos-1] = number[3];
			break;
			case '4':
			buf[pos-1] = number[4];
			break;
			case '5':
			buf[pos-1] = number[5];
			break;
			case '6':
			buf[pos-1] = number[6];
			break;
			case '7':
			buf[pos-1] = number[7];
			break;
			case '8':
			buf[pos-1] = number[8];
			break;
			case '9':
			buf[pos-1] = number[9];
			break;
			
			default:
			buf[pos-1] = number[CHARACTER_];
		}
	
}

void IND_OutputText(const char* text, unsigned char comma)
{
	 unsigned char i;
	 unsigned char pre_buf[AMOUNT_NUM] = {0, 0, 0, 0}; // pre_buf we use becouse: updating display occures with big fraquancy - every 2ms and in the interupts - so it 
		                                               // could indid update the same buf[] value it is needed to change buf[] in the shortest time  as posible.
	 for(i = 0; i < AMOUNT_NUM; i++)  //кожну букву
	 {
		 switch (text[i])
		 {
			 case 'o':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_o];
			 break;
			 case 'p':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_p];
			 break;
			 case 'n':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_n];
			 break;
			 case 'd':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_d];
			 break;
			 case 'y':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_y];
			 break;
			 case 't':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_t];
			 break;
			 case 'e':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_e];
			 break;
			 case 'r':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_r];
			 break;
			 case 'l':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_l];
			 break;
			 case 'i':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_i];
			 break;
			 case 'a':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_a];
			 break;
			 case 'g':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_g];
			 break;
			 case 's':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_s];
			 break;
			 case 'c':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_c];
			 break;
			 case 'u':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_u];
			 break;
			 case '-':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_minus];
			 break;
			 case '*':
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_degree];
			 break;
			 
			 case '0':
			 pre_buf[AMOUNT_NUM-1-i] = number[0];
			 break;
			 case '1':
			 pre_buf[AMOUNT_NUM-1-i] = number[1];
			 break;
			 case '2':
			 pre_buf[AMOUNT_NUM-1-i] = number[2];
			 break;
			 case '3':
			 pre_buf[AMOUNT_NUM-1-i] = number[3];
			 break;
			 case '4':
			 pre_buf[AMOUNT_NUM-1-i] = number[4];
			 break;
			 case '5':
			 pre_buf[AMOUNT_NUM-1-i] = number[5];
			 break;
			 case '6':
			 pre_buf[AMOUNT_NUM-1-i] = number[6];
			 break;
			 case '7':
			 pre_buf[AMOUNT_NUM-1-i] = number[7];
			 break;
			 case '8':
			 pre_buf[AMOUNT_NUM-1-i] = number[8];
			 break;
			 case '9':
			 pre_buf[AMOUNT_NUM-1-i] = number[9];
			 break;
			 
			 default:
			 pre_buf[AMOUNT_NUM-1-i] = number[CHARACTER_];
		 }
	 }
 
 if ( (comma < AMOUNT_NUM+1)&& (comma !=0) )
 {
	 pre_buf[comma-1] |= 1<<(SEG_DP);	 
 }
 for(i = 0; i < AMOUNT_NUM; i++)
 {
	  buf[i] = pre_buf[i];  // pre_buf we use becouse: updating display occures with big fraquancy - every 2ms and in the interupts - so it
	  // could indid update the same buf[] value it is needed to change buf[] in the shortest time  as posible.
 }
}
//************************************************************************
void IND_OutputInteger(unsigned int value, unsigned char comma)
{
  
	 unsigned char i;
	 unsigned char tmp;
	 unsigned char pre_buf[AMOUNT_NUM] = {0, 0, 0, 0};
	 for(i = 0; i < AMOUNT_NUM; i++)
	 {
		 tmp = value % 10;
		 pre_buf[i] = number[tmp];
		 value = value/10;
	 }
	 // in this section we prevent 0 to be displayed in higher bits positions
	 if ( (pre_buf[3] == number[0])&& (comma!=4))
	 {
		 pre_buf[3] =  number[CHARACTER_];
		 if ((pre_buf[2] == number[0]) && (comma!=3))
		 {
			 pre_buf[2] = number[CHARACTER_];
			 if ((pre_buf[1]==number[0]) && (comma!=2))
			 {
				 pre_buf[1] = number[CHARACTER_];
			 }
		 }
	 }
	 
		 
	 if ( (comma < AMOUNT_NUM+1)&& (comma !=0) )
	 {
		 pre_buf[comma-1] |= 1<<(SEG_DP);
	 }
	 for(i = 0; i < AMOUNT_NUM; i++)
	 {
		 buf[i] = pre_buf[i];	// pre_buf we use becouse: updating display occures with big fraquancy - every 2ms and in the interupts - so it
		 // could indid update the same buf[] value it is needed to change buf[] in the shortest time  as posible.
	 }
}
   
void FullOffIND (void)
{
	PORT_IND = 0;
	LightOutAll();
}

//***********************************************************************
void IND_Update(void)
{
  static unsigned char count = 0;
  
  //гасим все индикаторы
  FullOffIND();
  
  //"поджигаем" нужное знакоместо 
  if (count == 0) BurnDigit(PORT_TR, NUM1);
  else if (count == 1) BurnDigit(PORT_TR, NUM2);
  else if (count == 2) BurnDigit(PORT_TR, NUM3);
  else BurnDigit(PORT_TR, NUM4);
  
  //загружаем в порт символ
  PORT_IND = ValueBuf();
  
  count++;
  if (count == AMOUNT_NUM) count = 0;
}



repeatingHandler blickOn;
repeatingHandler blickOff;
void IND_Upd_bliks (void)
{
    static bool light_on = false;
    if (light_on)    //  make light on for some period
    {
	   
	   if (blickOn.repeat(BLICKON)) light_on = false;
	   IND_Update();	    
    }
    else       // turn off for some period
    {
	   LightOutAll();
	   if (blickOff.repeat(BLICKOFF)) light_on = true;	   
	   
    }
}
