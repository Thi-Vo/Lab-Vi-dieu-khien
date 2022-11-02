/*
 * global_variable.h
 *
 *  Created on: 24 Oct 2022
 *      Author: DLCH
 */

#ifndef INC_GLOBAL_VARIABLE_H_
#define INC_GLOBAL_VARIABLE_H_

#include "main.h"
#include "input_reading.h"
#include "led_display.h"
#include "timer.h"
#include "fsm.h"

extern uint32_t red_time;
extern uint32_t yellow_time;
extern uint32_t green_time;

extern uint32_t temp_red_time;
extern uint32_t temp_green_time;
extern uint32_t temp_yellow_time;

extern uint8_t road1_buffer[2];
extern uint8_t road2_buffer[2];

//define a fsm with 9 state
enum status{
	INIT = 0,				//initial state
	S1 = 1,					//1 green, 2 red
	S2 = 2,					//1 yellow, 2 red
	S3 = 3,					//1 red, 2 red
	S4 = 4,					//1 red, 2 green
	S5 =5,					//1 red, 2 yellow
	RED_ADJUST = 11,		//adjust time of red led
	YELLOW_ADJUST = 12,		//adjust time of amber led
	GREEN_ADJUST = 13		//adjust time of green led
};


extern enum status state;


extern uint8_t led_scanning;

//time to change between 4 seven segment led
//250ms -> f(4led) = 1Hz
#define SCANNING_TIME 250

#endif /* INC_GLOBAL_VARIABLE_H_ */
