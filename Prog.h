/* 
* Prog.h
*
* Created: 21.01.2016 9:39:26
* Author: Alex
*/


#ifndef __PROG_H__
#define __PROG_H__

// here is the class for P1-P9 programs.It includes 3 durations for t komf, function to get temperature
class Prog
{
//variables
public:

int t1_on;
int t1_off;
int t2_on;
int t2_off;
int t3_on;
int t3_off;

protected:
private:

 

//functions
public:
	Prog(long int, long int, long int, long int, long int, long int);
	~Prog();

float SetRoomTempr (float t_room_comfortable, float t_room_eco);


protected:
private:
	Prog( const Prog &c );
	Prog& operator=( const Prog &c );

}; //Prog

#endif //__PROG_H__
