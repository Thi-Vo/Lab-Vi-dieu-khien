/*
 * fsm.c
 *
 *  Created on: 24 Oct 2022
 *      Author: DLCH
 */
#include "fsm.h"

//***********//
//We use 5 timer:
//	1. Control road 1
//	2. Control road 2
//	3. Scanning 7seg led
//	4. Countdown in 5 auto state
//	5. Blink led 2Hz in 3 manual state
//-----------------------------------------
//This fsm have 9 state
//	1. INIT: check if (yellow+green > red) -> error (not happen in reality)
//			 error: all 7seg led display 8 and waiting for mode_button press to adjust time
// 			 if not error, turn to state S1
//	2. S1  : road1 green, road2 red
//	3. S2  : road1 yellow, road2 red
//	4. S3  : road1 red, road2 red (happen when red > yellow + green)
// 	5. S4  : road1 red, road2 green
//  6. S5  : road1 red, road2 yellow
//	7. RED_ADJUST: blink led, display mode=2 and time red while adjusting with time_button
//	8. YELLOW_ADJUST: display mode = 3, others are the same as above
//	9. GREEN_ADJUST: display mode = 4, others are the same as above
//***********//

void fsm_run()
{
	switch(state)
	{
	case INIT:
		if(yellow_time + green_time > red_time){
			//error state
			update_buffer_when_error();
			turn_all_led_on();
			sevenSegAuto();

			//trap here until mode_button is pressed
			//and go to RED_ADJUST mode to change value again
			if(is_mode_select_button_pressed()){
				state = RED_ADJUST;
				update_buffer_manual(2, temp_red_time);
				setTimer5(250);
				//reset all button flag
				is_set_button_pressed();
				is_time_adjust_button_pressed();
			}
			break;
		}
		//no error, prepare for changing to S1
		setTimer1(green_time);
		setTimer2(red_time);

		set_road1_buffer(green_time);
		set_road2_buffer(red_time);

		setTimer3(SCANNING_TIME);
		setTimer4(1000);

		state = S1;
		break;
	case S1:
		green1_on();
		red2_on();
		sevenSegAuto();
		updateBufferAuto();

		//road1 timeout -> turn to S2
		if(timer1_flag == 1){
			setTimer1(yellow_time);
			set_road1_buffer(yellow_time);
			state = S2;
		}

		//Mode_button is pressed -> turn to RED_ADJUST
		if(is_mode_select_button_pressed()){
			state = RED_ADJUST;
			update_buffer_manual(2, temp_red_time);
			setTimer5(250);
			//reset all button flag
			is_time_adjust_button_pressed();
			is_set_button_pressed();
		}
		break;
	case S2:
		yellow1_on();
		red2_on();
		sevenSegAuto();
		updateBufferAuto();

		//road1 timeout -> turn to S3
		if(timer1_flag == 1){
			setTimer1(red_time);
			set_road1_buffer(red_time);
			state = S3;
		}

		//Mode_button is pressed -> turn to RED_ADJUST
		if(is_mode_select_button_pressed()){
			state = RED_ADJUST;
			update_buffer_manual(2, temp_red_time);
			setTimer5(250);
			//reset all button flag
			is_time_adjust_button_pressed();
			is_set_button_pressed();
		}
		break;
	case S3:
		red1_on();
		red2_on();
		sevenSegAuto();
		updateBufferAuto();

		//road1 timeout -> turn to S1
		if(timer1_flag == 1){
			setTimer1(green_time);
			set_road1_buffer(green_time);
			state = S1;
		}
		//road2 timeout -> turn to S4
		if(timer2_flag == 1){
			setTimer2(green_time);
			set_road2_buffer(green_time);
			state = S4;
		}

		//Mode_button is pressed -> turn to RED_ADJUST
		if(is_mode_select_button_pressed()){
			state = RED_ADJUST;
			update_buffer_manual(2, temp_red_time);
			setTimer5(250);
			//reset all button flag
			is_time_adjust_button_pressed();
			is_set_button_pressed();
		}
		break;
	case S4:
		red1_on();
		green2_on();
		sevenSegAuto();
		updateBufferAuto();

		//road2 timeout -> turn to S5
		if(timer2_flag == 1){
			setTimer2(yellow_time);
			set_road2_buffer(yellow_time);
			state = S5;
		}

		//Mode_button is pressed -> turn to RED_ADJUST
		if(is_mode_select_button_pressed()){
			state = RED_ADJUST;
			update_buffer_manual(2, temp_red_time);
			setTimer5(250);
			//reset all button flag
			is_time_adjust_button_pressed();
			is_set_button_pressed();
		}
		break;
	case S5:
		red1_on();
		yellow2_on();
		sevenSegAuto();
		updateBufferAuto();

		//road2 timeout -> turn to S3
		if(timer2_flag == 1){
			setTimer2(red_time);
			set_road2_buffer(red_time);
			state = S3;
		}

		//Mode_button is pressed -> turn to RED_ADJUST
		if(is_mode_select_button_pressed()){
			state = RED_ADJUST;
			update_buffer_manual(2, temp_red_time);
			setTimer5(250);
			//reset all button flag
			is_time_adjust_button_pressed();
			is_set_button_pressed();
		}
		break;
	case YELLOW_ADJUST:
		yellow_blink();
		sevenSegAuto();

		//when time_button pressed -> increase time by 1
		//when keep pressing -> increase 1 every 1 second
		//range of time is [1-99]
		if(is_time_adjust_button_pressed() || is_time_adjust_button_press1s()){
			temp_yellow_time = temp_yellow_time% 99000 + 1000;
			update_buffer_manual(3, temp_yellow_time);
		}

		//set_button is pressed -> save temp value
		if(is_set_button_pressed()){
			yellow_time = temp_yellow_time;
		}

		//Mode_button is pressed -> turn to GREEN_ADJUST
		if(is_mode_select_button_pressed()){
			state = GREEN_ADJUST;
			update_buffer_manual(4, temp_green_time);
			setTimer5(250);
			//reset all button flag
			is_time_adjust_button_pressed();
			is_set_button_pressed();
		}
		break;
	case GREEN_ADJUST:
		green_blink();
		sevenSegAuto();

		//when time_button pressed -> increase time by 1
		//when keep pressing -> increase 1 every 1 second
		//range of time is [1-99]
		if(is_time_adjust_button_pressed() || is_time_adjust_button_press1s()){
			temp_green_time = temp_green_time% 99000 + 1000;
			update_buffer_manual(4, temp_green_time);
		}

		//set_button is pressed -> save temp value
		if(is_set_button_pressed()){
			green_time = temp_green_time;
		}

		//Mode_button is pressed -> turn to INIT
		if(is_mode_select_button_pressed()){
			state = INIT;
			//reset all button flag
			is_time_adjust_button_pressed();
			is_set_button_pressed();
		}
		break;
	case RED_ADJUST:
		red_blink();
		sevenSegAuto();

		//when time_button pressed -> increase time by 1
		//when keep pressing -> increase 1 every 1 second
		//range of time is [1-99]
		if(is_time_adjust_button_pressed() || is_time_adjust_button_press1s()){
			temp_red_time = temp_red_time% 99000 + 1000;
			update_buffer_manual(2, temp_red_time);
		}
		//set_button is pressed -> save temp value
		if(is_set_button_pressed()){
			red_time = temp_red_time;
		}

		//Mode_button is pressed -> turn to YELLOW_ADJUST
		if(is_mode_select_button_pressed()){
			state = YELLOW_ADJUST;
			update_buffer_manual(3, temp_yellow_time);
			setTimer5(250);
			//reset all button flag
			is_time_adjust_button_pressed();
			is_set_button_pressed();
		}
		break;
	default:
		break;
	}
}
