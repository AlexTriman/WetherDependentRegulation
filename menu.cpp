#include <avr/io.h>
//#include <avr/pgmspace.h>
#include "global_varibals.h"
#include "menu.h"
#include "digitsdisplay.h"
#include "climate.h"
#include "Timing.h"

/*
 вгору вниз - дві фужнкції: переміщення , редагування(зміна параматра)
 функція вибору приймає параметр плюс чи мінус, яку вона змінює, а повертає змінену змінну

 відображення на екран

*/

menuItem	Null_Menu = {(void*)0, (void*)0, (void*)0, (void*)0, SHOW_TEXT, NONE};



//                 NEXT,      PREVIOUS     PARENT,     CHILD         displayoption  show
MAKE_MENU(m_1,    m_2,        m_7,         m_4,        m_1_1,        SHOW_PARAMETER, T_KOMF);  //"Тkomf"
MAKE_MENU(m_2,    m_3,        m_1,         m_4,        m_2_1,        SHOW_PARAMETER, T_ECO);  //"Тeco"
MAKE_MENU(m_3,    m_4,        m_2,         m_4,        NULL_ENTRY,   SHOW_PARAMETER, T_OUTSIDE);  //"Toutside"
MAKE_MENU(m_4,    m_5,        m_3,         NULL_ENTRY, NULL_ENTRY,   SHOW_PARAMETER, T_FLOW);   //"Tflow"
MAKE_MENU(m_5,    m_6,        m_4,         m_4,        NULL_ENTRY,   SHOW_PARAMETER, T_SET);  //"Tset"
MAKE_MENU(m_6,    m_7,        m_5,         m_4,        m_6_1,        SHOW_PARAMETER, PROG);  //"PROG"
MAKE_MENU(m_7,    m_1,        m_6,         m_4,        m_7_1,        SHOW_PARAMETER, MENU);  //"MENU"

// подменю Tkomf edit (m_1_1)
MAKE_MENU(m_1_1,  NULL_ENTRY, NULL_ENTRY,  m_1,        NULL_ENTRY,  EDIT_PARAMETER, T_KOMF_); //"Tkomf edit"


// подменю Teco edit (m_2_1)SHOW_PARAMETER_BLICK
MAKE_MENU(m_2_1,  NULL_ENTRY, NULL_ENTRY,  m_2,        NULL_ENTRY,   EDIT_PARAMETER, T_ECO_); //"Teco edit"


// подменю PROG (m_6_1..7)
MAKE_MENU(m_6_1,  m_6_2,      m_6_7,       m_6,        m_6_1_,   SHOW_PARAMETER, MO);  //"Пн"  day1
MAKE_MENU(m_6_2,  m_6_3,      m_6_1,       m_6,        m_6_2_,   SHOW_PARAMETER, TU);  //"Вт"
MAKE_MENU(m_6_3,  m_6_4,      m_6_2,       m_6,        m_6_3_,   SHOW_PARAMETER, WE); //"Ср"
MAKE_MENU(m_6_4,  m_6_5,      m_6_3,       m_6,        m_6_4_,   SHOW_PARAMETER, TH);  //"Чт"
MAKE_MENU(m_6_5,  m_6_6,      m_6_4,       m_6,        m_6_5_,   SHOW_PARAMETER, FR);  //"Пт"
MAKE_MENU(m_6_6,  m_6_7,      m_6_5,       m_6,        m_6_6_,   SHOW_PARAMETER, SA); //"Сб"
MAKE_MENU(m_6_7,  m_6_1,      m_6_6,       m_6,        m_6_7_,   SHOW_PARAMETER, SU);  //"Нд"

MAKE_MENU(m_6_1_,  NULL_ENTRY,      NULL_ENTRY,       m_6_1,        NULL_ENTRY,   EDIT_PARAMETER, MO_P);  //"Пн"  day1
MAKE_MENU(m_6_2_,  NULL_ENTRY,      NULL_ENTRY,       m_6_2,        NULL_ENTRY,   EDIT_PARAMETER, TU_P);  //"Вт"
MAKE_MENU(m_6_3_,  NULL_ENTRY,      NULL_ENTRY,       m_6_3,        NULL_ENTRY,   EDIT_PARAMETER, WE_P); //"Ср"
MAKE_MENU(m_6_4_,  NULL_ENTRY,      NULL_ENTRY,       m_6_4,        NULL_ENTRY,   EDIT_PARAMETER, TH_P);  //"Чт"
MAKE_MENU(m_6_5_,  NULL_ENTRY,      NULL_ENTRY,       m_6_5,        NULL_ENTRY,   EDIT_PARAMETER, FR_P);  //"Пт"
MAKE_MENU(m_6_6_,  NULL_ENTRY,      NULL_ENTRY,       m_6_6,        NULL_ENTRY,   EDIT_PARAMETER, SA_P); //"Сб"
MAKE_MENU(m_6_7_,  NULL_ENTRY,      NULL_ENTRY,       m_6_7,        NULL_ENTRY,   EDIT_PARAMETER, SU_P);  //"Нд"


// подменю Menu
MAKE_MENU(m_7_1,   m_7_3,      m_7_7,         m_7,     m_7_1_,   SHOW_PARAMETER, CURVE); //curve
//MAKE_MENU(m_7_2,   m_7_3,      m_7_1,         m_7,     m_7_2_,   SHOW_PARAMETER, SERVO); //servo
MAKE_MENU(m_7_3,   m_7_4,      m_7_1,         m_7,     m_7_3_,   SHOW_PARAMETER, P); // p
MAKE_MENU(m_7_4,   m_7_5,      m_7_3,         m_7,     m_7_4_,   SHOW_PARAMETER, I); //i
MAKE_MENU(m_7_5,   m_7_6,      m_7_4,         m_7,     m_7_5_,   SHOW_PARAMETER, D); //d
MAKE_MENU(m_7_6,   m_7_7,      m_7_5,         m_7,     m_7_6_,   SHOW_PARAMETER, TIME); //t
MAKE_MENU(m_7_7,   m_7_1,      m_7_6,         m_7,     m_7_7_,   SHOW_PARAMETER, DAYOFWEEK); // day   I

//                     NEXT,      PREVIOUS     PARENT,     CHILD
// пыдменю on/off edit
MAKE_MENU(m_7_1_,  NULL_ENTRY, NULL_ENTRY,    m_7_1,     NULL_ENTRY,   EDIT_PARAMETER, CURVE_); //"I"
//MAKE_MENU(m_7_2_,  NULL_ENTRY, NULL_ENTRY,    m_7_2,     NULL_ENTRY,   EDIT_PARAMETER, SERVO_); //"I"
MAKE_MENU(m_7_3_,  NULL_ENTRY, NULL_ENTRY,    m_7_3,     NULL_ENTRY,   EDIT_PARAMETER, P_); //"I"
MAKE_MENU(m_7_4_,  NULL_ENTRY, NULL_ENTRY,    m_7_4,     NULL_ENTRY,   EDIT_PARAMETER, I_); //"I"
MAKE_MENU(m_7_5_,  NULL_ENTRY, NULL_ENTRY,    m_7_5,     NULL_ENTRY,   EDIT_PARAMETER, D_); //"I"
MAKE_MENU(m_7_6_,  NULL_ENTRY, NULL_ENTRY,    m_7_6,     NULL_ENTRY,   EDIT_PARAMETER, TIME_); //"I"
MAKE_MENU(m_7_7_,  NULL_ENTRY, NULL_ENTRY,    m_7_7,     NULL_ENTRY,   EDIT_PARAMETER, DAYOFWEEK_); //"I"

menuItem *selectedMenuItem;
                               
// ініціалізація меню
void Menu_Ini(void)
{
	selectedMenuItem = &m_4;			
}  

// this function is called out when +/- buttons are pressed and we are in the editing mode (the editing mode appears when "Enter" has been pressed)
// the_parameter - what parameter is going to be edited
// the sign - what the button has been pressed + or - (1 or -1 when multiplying)
void Editing (Parameter the_edited_parameter, int the_sign)
{
		  	  
	switch (the_edited_parameter)
	{
		 case T_KOMF_:  // the room temperature set comfortable
		 t_room_comfortable_G += the_sign * 0.5;
		 if (t_room_comfortable_G>=38 ) t_room_comfortable_G = 38;
		 if (t_room_comfortable_G<=2) t_room_comfortable_G = 2;
		 break;
		 		 		 
		 case T_ECO_:
		 t_room_eco_G += 0.5*the_sign;
		 if (t_room_eco_G>=38 ) t_room_eco_G = 38;
		 if (t_room_eco_G<=2) t_room_eco_G = 2;
		 break;					 		 
		 
		 case T_SET:
		 t_flow_setpoint_G += 0.5*the_sign;
		 break;			 		
		 
		 case MO_P:
		 day_prog[0] = ChangeProg(0,day_prog,the_sign);
		 break;
		 
		 case TU_P:
		 day_prog[1] = ChangeProg(1,day_prog,the_sign);
		 break;
		 
		 case WE_P:
		 day_prog[2] = ChangeProg(2,day_prog,the_sign);
		 break;
		 
		 case TH_P:
		 day_prog[3] = ChangeProg(3,day_prog,the_sign);
		 break;
		 
		 case FR_P:
		 day_prog[4] = ChangeProg(4,day_prog,the_sign);
		 break;
		 
		 case SA_P:
		 day_prog[5] = ChangeProg(5,day_prog,the_sign);
		 break;
		 
		 case SU_P:
		 day_prog[6] = ChangeProg(6,day_prog,the_sign);
		 break;
		 
		 case CURVE_:
		 heating_curve_G += 0.1*the_sign; 
		 if (heating_curve_G>7) heating_curve_G=7;
		 if (heating_curve_G<0.5) heating_curve_G = 0.5;
		 break;
		 
		 /*
		 case SERVO_:
		 servo_period_G += 1000*the_sign;
		 break;
		 */
		 case P_:
		 Kp_G += 1*the_sign;
		 if(Kp_G>1000) Kp_G=1000;
		 if (Kp_G<0) Kp_G=0;		 
		 break;
		 
		 case I_:
		 Ki_G += 1*the_sign;		 
		 if (Ki_G>1000) Ki_G=1000;
		 if (Ki_G<0) Ki_G = 0;
		 break;
		 
		 case D_:
		 Kd_G += 1*the_sign;	
		 if (Kd_G>1000) Kd_G=1000;
		 if (Kd_G<0) Kd_G = 0;		 
		 break;
		 
		 case TIME_:
		 our_time[MINUTES]+=1*the_sign;
		 if (our_time[MINUTES]>=60)
		 {
		  our_time[MINUTES]=0;
		  our_time[HOURE]++;
		 }		 
		 if (our_time[MINUTES]<0)
		 {
			  our_time[HOURE]--;
			  our_time[MINUTES]=59;
		 }
		 if (our_time[HOURE]>=24) our_time[HOURE]=0;
		 if (our_time[HOURE]<0) our_time[HOURE]=23;
		 // перевіряємо  не змінився час в процесі коли користувач налаштовує годинник (може мати менше значення
	
		 		 
		 break;
		 
		 case DAYOFWEEK_:
		 our_time[WEEKDAY]+=1*the_sign;
		 if(our_time[WEEKDAY]>7) our_time[WEEKDAY]=1;
		 if(our_time[WEEKDAY]<1) our_time[WEEKDAY]=7;		 		 		 
		 break;
		 
		 case RESERVE:
		 
		 break;
		 
		 default:
		 break;	 
	}	
}
  
#define PREVIOUS    static_cast<menuItem*>(selectedMenuItem->Previous)
#define NEXT        static_cast<menuItem*>(selectedMenuItem->Next)
#define PARENT      static_cast<menuItem*>(selectedMenuItem->Parent)
#define CHILD       static_cast<menuItem*>(selectedMenuItem->Child)
 
void menuChange(menuItem *NewMenu)
{
	if (NewMenu == (void*)&NULL_ENTRY)	 return;
		
	selectedMenuItem = NewMenu;	
}



// this function takes the button value which has been pressed and provides the reaction


 
//**************************************** Navigate menu itemes
void keyMenu(ButtonValues the_key)
{

	switch (the_key) // what the key has been pressed?
	{
		case UP:
		{
						
			//chek out what shoud we do 1) edit 2) show parameter 3) just go
			if  ( (selectedMenuItem->display_option) == EDIT_PARAMETER)			                 
			{				
				Editing (selectedMenuItem->edited_parameter, 1);
				break;				
			}
			else 
			{				 
				 menuChange(PREVIOUS);			 
			}
		}
		break;
		
				
		case DOWN:				
			if  ( (selectedMenuItem->display_option) == EDIT_PARAMETER)
			{
				Editing (selectedMenuItem->edited_parameter, -1);
				break;	
			}			
			else
			{				
				menuChange(NEXT);
			}
		break;
			
		case ESC:		  
		   menuChange(PARENT);		   
		break;
		
		case ENTER:					
			if  (selectedMenuItem->display_option == EDIT_PARAMETER)
			{
				menuChange(PARENT);				
			} 
			else
			{
				 menuChange(CHILD);				
			}
		break;

		default:
		break;
 	}
}


Parameter GetEditedParameter (void)
{
	return selectedMenuItem->edited_parameter;
}



led_num chosen_led_G = TFLOW_LED;
bool sens_err_G = false;



void RenewScreen (void)
{
	Parameter parameter = NONE;
	
	parameter=GetEditedParameter ();
				
				// update display information
				//what parameter to display
					
					unsigned int value;
					 
					switch (parameter)
				
					{
					   case T_KOMF:						
				       value = (t_room_comfortable_G+0.5)*100;
					   IND_OutputInteger(value, 3);
					   IND_OutputSymbol("*", 1);					   
					   chosen_led_G = TCOMF_LED;   //chose regarding led
					   blick_screen_G=false;
					   break;	
					   
					   case T_KOMF_:
					   value = (t_room_comfortable_G+0.5)*100;
					   IND_OutputInteger(value, 3);
					   IND_OutputSymbol("*", 1);
					   chosen_led_G = TCOMF_LED;   //chose regarding led
					   blick_screen_G=true;
					   break;
					   
					   									
					   case T_ECO:					   
					   value = (t_room_eco_G+0.5)*100;
					   IND_OutputInteger(value, 3);
					   IND_OutputSymbol("*", 1);
					   blick_screen_G=false;
					   chosen_led_G = TECO_LED;   //chose regarding led
					   break;
					   
					   	case T_ECO_:
					   	value = (t_room_eco_G+0.5)*100;
					   	IND_OutputInteger(value, 3);
					   	IND_OutputSymbol("*", 1);
					   	blick_screen_G=true;
					   	chosen_led_G = TECO_LED;   //chose regarding led
					   	break;
					 //////////////  
					   case T_OUTSIDE:
					   chosen_led_G = TOUTSIDE_LED;   //chose regarding led
					   if (sens_err_G) 
					   {
						 IND_OutputText("err ",0);  
						 blick_screen_G=true; 
						 break;
					   }
					   if (t_outside_G<0)  //for values under 0 degree
						{
							value = static_cast<unsigned int>(t_outside_G*(-100));						   
							if (value >= 1000)  // for values under -10
							{
								value = value/10;
								IND_OutputInteger(value, 0);
								IND_OutputSymbol("-", 4);
								IND_OutputSymbol("*", 1);
							}
							else  // 0 to -10
							{
								IND_OutputInteger(value, 3);
								IND_OutputSymbol("-", 4);
								IND_OutputSymbol("*", 1);   
							}				   
						   
						}
						else 
						{
							value = t_outside_G*100;
							IND_OutputInteger(value, 3);
							IND_OutputSymbol("*", 1);   
						}						
					   break;
					///////////////////   
					   case T_FLOW:
					   chosen_led_G = TFLOW_LED;   //chose regarding led	
					   if (sens_err_G) 					   
					   {
						    IND_OutputText("err ",0);	
							blick_screen_G=true;						
							break;
					   }					   					  
						value = (t_flow_G+0.5)*10;
						IND_OutputInteger(value, 0);
						IND_OutputSymbol("*", 1);									   
					   break;	   
					///////////////   				   
					   case T_SET:
					   value = (t_flow_setpoint_G+0.5)*10;
					   IND_OutputInteger(value, 0);
					   IND_OutputSymbol("*", 1);
					   blick_screen_G=false;
					   chosen_led_G = TSET_LED;   //chose regarding led
					   break;
					///////////////   
					   case PROG:
					   IND_OutputText("prog",0);
					   blick_screen_G=false;
					   chosen_led_G = PROG_LED;
					   break;
					   
					   case MENU:
					   IND_OutputText("set", 0);
					   blick_screen_G=false;
					   chosen_led_G = MENU_LED;
					   break;
					   
					   case MO:
					   IND_OutputText(TextProgNum(0,day_prog), 0);
					   blick_screen_G=false;
					   chosen_led_G = MO_LED; 
					   break;
					   
					   case TU:
					   IND_OutputText(TextProgNum(1,day_prog), 0);
					   blick_screen_G=false;
					   chosen_led_G = TU_LED;
					   break;
					   
					   case WE:
					   IND_OutputText(TextProgNum(2,day_prog), 0);
					   blick_screen_G=false;
					   chosen_led_G = WE_LED;
					   break;
					   
					   case TH:
					   IND_OutputText(TextProgNum(3,day_prog), 0);
					   blick_screen_G=false;
					   chosen_led_G = TH_LED;
					   break;
					   
					   case FR:
					   IND_OutputText(TextProgNum(4,day_prog), 0);
					   blick_screen_G=false;
					   chosen_led_G = FR_LED;
					   break;
					   
					   case SA:
					   IND_OutputText(TextProgNum(5,day_prog), 0);
					   blick_screen_G=false;
					   chosen_led_G = SA_LED;
					   break;
					   				   
					   case SU:
					   IND_OutputText(TextProgNum(6,day_prog), 0);
					   blick_screen_G=false;
					   chosen_led_G = SU_LED;					 
					   break;			   
					
							case MO_P:
							IND_OutputText(TextProgNum(0,day_prog), 0);		
							blick_screen_G=true;					
							break;
					   
							case TU_P:
							IND_OutputText(TextProgNum(1,day_prog), 0);	
							blick_screen_G=true;						
							break;
					    
							case WE_P:
							IND_OutputText(TextProgNum(2,day_prog), 0);	
							blick_screen_G=true;						
							break;
					    
							case TH_P:
							IND_OutputText(TextProgNum(3,day_prog), 0);	
							blick_screen_G=true;						
							break;
					    
							case FR_P:
							IND_OutputText(TextProgNum(4,day_prog), 0);	
							blick_screen_G=true;						
							break;
					    
							case SA_P:
							IND_OutputText(TextProgNum(5,day_prog), 0);	
							blick_screen_G=true;						
							break;
					    
							case SU_P:
							IND_OutputText(TextProgNum(6,day_prog), 0);	
							blick_screen_G=true;						
							break;
					   
					   case CURVE:
					   IND_OutputText(" cur", 0);
					   blick_screen_G=false;
					   break;
					   /*
					   case SERVO:
					   IND_OutputText("ser ", 0);
					   break;
					   */
					   case P:
					   IND_OutputText("ppid", 0);
					   blick_screen_G=false;
					   break;
					   
					   case I:
					   IND_OutputText("ipid", 0);
					   blick_screen_G=false;
					   break;
					   
					   case D:
					   IND_OutputText("dpid", 0);
					   blick_screen_G=false;
					   break;
					   
					   case TIME:
					   IND_OutputText("cloc", 0);
					   blick_screen_G=false;
					   break;
					   
					   case DAYOFWEEK:
					   IND_OutputText(" day", 0);
					   blick_screen_G=false;
					   break;
					   
					   case RESERVE:
					   
					   break;
					   		 		   
					   case CURVE_:
					   value = heating_curve_G*10;
					   IND_OutputInteger(value,2);
					   blick_screen_G=true;
					   break;
					   /*
					   case SERVO_:
					   value = servo_period_G/1000;
					   IND_OutputInteger(value, 0);
					   break;  
					   */
					   case P_:
					   value = Kp_G;
					   IND_OutputInteger(value, 0);
					   blick_screen_G=true;
					   break;
					   
					   case I_:
					   value = Ki_G;
					   IND_OutputInteger(value, 0);
					   blick_screen_G=true;
					   break;
					   
					   case D_:
					   value = Kd_G;
					   IND_OutputInteger(value, 0);
					   blick_screen_G=true;
					   break;
					   
					   case TIME_:
					   value=our_time[HOURE]*100+our_time[MINUTES];
					   IND_OutputInteger(value, 3);			
					   blick_screen_G=true;		
					   break;
									   
					   case DAYOFWEEK_:
					   value=our_time[WEEKDAY];
					   IND_OutputInteger(value, 0);
					   blick_screen_G=true;
					   break;	   
					    	  		  
					  
					   default:
					   break;
					}
				
}