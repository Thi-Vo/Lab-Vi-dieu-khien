/*
 * input_reading.c
 *
 *  Created on: Oct 14, 2022
 *      Author: DLCH
 */
#include "input_reading.h"

//number of button we have
#define N0_OF_BUTTONS 				       3
//timer interrupt duration is 10ms, so to pass 1 second,
//we need to jump to the interrupt service routine 100 time
#define DURATION_FOR_PRESSED	   		   100
#define BUTTON_IS_PRESSED                  GPIO_PIN_RESET
#define BUTTON_IS_RELEASED                 GPIO_PIN_SET

//the buffer that the final result is stored after debouncing
static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];

//we define three buffers for debouncing
static GPIO_PinState debounceButtonBuffer0[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS];

//we define flags for button pressed
static uint8_t flagForButtonPress1s[N0_OF_BUTTONS] = {0};
static uint8_t flagForButtonPress[N0_OF_BUTTONS] = {0};

//we define counter for the button is pressed more than 1 second.
static uint16_t counterForButtonPress1s[N0_OF_BUTTONS];

//read 3 button and modify flag buffer when button is pressed
//this function is called in timer interupt
void button_reading(){
	for(int i = 0; i < N0_OF_BUTTONS; i ++){
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = debounceButtonBuffer0[i];
		//read raw button to buffer0
		if(i == 0){
			debounceButtonBuffer0[i] = HAL_GPIO_ReadPin(Mode_select_button_GPIO_Port, Mode_select_button_Pin);
		}
		else if(i == 1){
			debounceButtonBuffer0[i] = HAL_GPIO_ReadPin(Time_adjust_button_GPIO_Port, Time_adjust_button_Pin);
		}
		else if(i == 2){
			debounceButtonBuffer0[i] = HAL_GPIO_ReadPin(Set_button_GPIO_Port, Set_button_Pin);
		}

		//if input is stable: 3 recently input is equal
		if(debounceButtonBuffer0[i] == debounceButtonBuffer1[i] &&
				debounceButtonBuffer1[i] == debounceButtonBuffer2[i]){
			//if input stable at present different from previous
			if(buttonBuffer[i] != debounceButtonBuffer2[i]){
				//update input to buffer
				buttonBuffer[i] = debounceButtonBuffer2[i];
				//if input is pressed
				if(buttonBuffer[i] == BUTTON_IS_PRESSED){
					//turn flag on
					flagForButtonPress[i] = 1;
					//set counter
					counterForButtonPress1s[i] = DURATION_FOR_PRESSED;
				}
			}
			//if input is stable and no change (present = previous)
			else{
				//decrease counter
				counterForButtonPress1s[i]--;
				//when counter is 0, reset counter
				//and if button is press -> turn flag1s on
				if(counterForButtonPress1s[i] == 0){
					if(buttonBuffer[i] == BUTTON_IS_PRESSED){
						flagForButtonPress1s[i] = 1;
					}
					counterForButtonPress1s[i] = DURATION_FOR_PRESSED;
				}
			}
		}
	}
}

//this function check if Mode_select_button is pressed or not
//and reset its flag
int is_mode_select_button_pressed()
{
	if(flagForButtonPress[0] == 1){
		flagForButtonPress[0] = 0;
		return 1;
	}
	return 0;
}

//this fuction check if time_adjust_button is pressed or not
//and reset its flag
int is_time_adjust_button_pressed()
{
	if(flagForButtonPress[1] == 1){
		flagForButtonPress[1] = 0;
		return 1;
	}
	return 0;
}

//this function check if time_adjust_button is keep pressed
//for 1 second and reset its flag
int is_time_adjust_button_press1s()
{
	if(flagForButtonPress1s[1] == 1){
		flagForButtonPress1s[1] = 0;
		return 1;
	}
	return 0;
}

//this function check if set_button is pressed or not
//and reset its flag
int is_set_button_pressed()
{
	if(flagForButtonPress[2] == 1){
		flagForButtonPress[2] = 0;
		return 1;
	}
	return 0;
}

