#include <pc.h>

#include "timer.h"

void timer_init(int timer, int mode){
	
	outportb(TIMER_CTRL, mode | (timer << 6));
	
	if(timer == 2)
	{
		char val = inportb(SPEAKER_CTRL);
		outportb(SPEAKER_CTRL, val | TIMER2_ENABLE);
	}
}

/** Load timer (0,1,2) with value
 */
void timer_load(int timer, int value){
	outportb(TIMER_0 | timer, LSB(value));
	outportb(TIMER_0 | timer, MSB(value));
}

void mili_sleep(int mili)
{
	int tempo = time_tick + mili;
	while(time_tick < tempo);
}

void sec_sleep(int secs)
{
	int tempo = sec_tick + secs;
	while(sec_tick < tempo);
}
