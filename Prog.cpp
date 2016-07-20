/* 
* Prog.cpp
*
* Created: 21.01.2016 9:39:25
* Author: Alex
*/


#include "Prog.h"
#include "global_varibals.h"
#include "Timing.h"

// default constructor
Prog::Prog(long int on1 = 0, long int off1 = 24*60, long int on2 = 0, long int off2 = 0, long int on3 = 0, long int off3 = 0)
{
	t1_on = on1;
	t1_off = off1;
	t2_on = on2;
	t2_off = off2;
	t3_on = on3;
	t3_off = off3;
} //Prog

// default destructor
Prog::~Prog()
{
} //~Prog


float Prog::SetRoomTempr (float t_room_comfortable, float t_room_eco)
	{
		
		long int minutes = our_time[HOURE]*60 + our_time[MINUTES];
		if ( (minutes >= t1_on && minutes < t1_off) || (minutes >= t2_on && minutes < t2_off) || (minutes >= t3_on && minutes < t3_off)  )
		{
			return t_room_comfortable;
		}
		else
		{
			return t_room_eco;
		}
		return t_room_comfortable;
	}
	
