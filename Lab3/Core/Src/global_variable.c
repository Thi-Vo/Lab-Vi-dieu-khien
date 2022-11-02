/*
 * global_variable.c
 *
 *  Created on: 24 Oct 2022
 *      Author: DLCH
 */

#include "global_variable.h"

//time of 3 led (ms)
uint32_t red_time = 10000;
uint32_t green_time = 7000;
uint32_t yellow_time = 3000;

//temporary time of 3 led
//use in adjusting mode
//when set_button is press, this value is copy to real time above
uint32_t temp_red_time = 1000;
uint32_t temp_green_time = 1000;
uint32_t temp_yellow_time = 1000;

//buffer for counting and displaying on 7seg led
uint8_t road1_buffer[2] = {0};
uint8_t road2_buffer[2] = {0};

//state use in fsm
enum status state = INIT;

//decide which 7seg led is to be turn on
//value in range [0,3]
//together with timer3[SCANNING_TIME] for scanning led
uint8_t led_scanning = 0;

