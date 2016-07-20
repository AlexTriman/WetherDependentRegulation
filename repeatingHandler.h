/* 
* timeHandler.h
*
* Created: 23.04.2016 21:51:58
* Author: Alex
*/


#ifndef __REPEATINGHANDLER_H__
#define __REPEATINGHANDLER_H__

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "digitsdisplay.h"
class repeatingHandler
{
//variables
public:
	uint16_t period;
	uint16_t ticks;		
	bool perform;	
	
protected:
private:

//functions
public:
	repeatingHandler();	
	~repeatingHandler();
		
	bool repeat (uint16_t period)
	{		
		if (period==0)
		{
			return false;  // out if period =0; don't repeat at all	
		}		
		if (perform==false)	
		{
			perform = true;		
			ticks = 0;
			return false;								
		}		
		
		if (perform==true)
		{
			if (ticks>=period)
			{
				perform = false;
				return true;
			}
			return false;
		}		
	}
protected:
private:
	/*repeatingHandler( const repeatingHandler &c );
	repeatingHandler& operator=( const repeatingHandler &c );*/

}; //timeHandler

#endif //__REPEATINGHANDLER_H__

