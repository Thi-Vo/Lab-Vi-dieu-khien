/*
 * timer.c
 *
 *  Created on: Oct 14, 2022
 *      Author: DLCH
 */
#include "timer.h"

const int TIMER_CYCLE = 10;

int timer1_flag = 0;
int timer1_counter = 0;

int timer2_flag = 0;
int timer2_counter = 0;

int timer3_flag = 0;
int timer3_counter = 0;

int timer4_flag = 0;
int timer4_counter = 0;

int timer5_flag = 0;
int timer5_counter = 0;

void setTimer1(uint32_t duration){
	timer1_counter = duration/TIMER_CYCLE;
	timer1_flag = 0;
}

void setTimer2(uint32_t duration){
	timer2_counter = duration/TIMER_CYCLE;
	timer2_flag = 0;
}

void setTimer3(uint32_t duration){
	timer3_counter = duration/TIMER_CYCLE;
	timer3_flag = 0;
}

void setTimer4(uint32_t duration){
	timer4_counter = duration/TIMER_CYCLE;
	timer4_flag = 0;
}

void setTimer5(uint32_t duration){
	timer5_counter = duration/TIMER_CYCLE;
	timer5_flag = 0;
}

void timerRun(){
	if(timer1_counter >0){
		timer1_counter--;
		if(timer1_counter <=0){
			timer1_flag =1;
		}
	}
	if(timer2_counter >0){
			timer2_counter--;
			if(timer2_counter <=0){
				timer2_flag =1;
			}
		}
	if(timer3_counter >0){
			timer3_counter--;
			if(timer3_counter <=0){
				timer3_flag =1;
			}
		}
	if(timer4_counter >0){
			timer4_counter--;
			if(timer4_counter <=0){
				timer4_flag =1;
			}
		}
	if(timer5_counter >0){
				timer5_counter--;
				if(timer5_counter <=0){
					timer5_flag =1;
				}
			}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		button_reading();
		timerRun();
}


