/*
 * led_display.c
 *
 *  Created on: Oct 14, 2022
 *      Author: DLCH
 */
#include "led_display.h"

//turn green led on road1 on
void green1_on()
{
	HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_SET);
}

//turn red led on road 1 on
void red1_on()
{
	HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_RESET);
}

//turn yellow led on road 1 on
void yellow1_on()
{
	HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_SET);
}

//turn green led on road 2 on
void green2_on()
{
	HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_SET);
}

//turn red led on road 2 on
void red2_on()
{
	HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_RESET);
}

//turn yellow led on road 2 on
void yellow2_on()
{
	HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_SET);
}

//display num to 7seg led
//a to g equal to SEG0 to SEG6
void display7SEG(int num)
{
	if(num==0 || num==2 || num==3 || num==5 || num==6
			|| num==7 || num==8 || num==9){
		HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_SET);

	if(num==0 || num==1 || num==2 || num==3 || num==4
		|| num==7 || num==8 || num==9){
		HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_SET);

	if(num==0 || num==1 || num==3 || num==4 || num==5 || num==6
			|| num==7 || num==8 || num==9){
		HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_SET);

	if(num==0 || num==2 || num==3 || num==5 || num==6 || num==8 ||num==9){
		HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_SET);

	if(num==0 || num==2 || num==6 || num==8){
		HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);

	if(num==0 || num==4 || num==5 || num==6 || num==8 ||num==9){
		HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_SET);

	if(num==2 || num==3 || num==4 || num==5 || num==6 || num==8 || num==9){
		HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_SET);

}


void set_road1_buffer(uint32_t time)
{
	uint32_t real_time = time/1000;		//time(ms), real_time(s)
	road1_buffer[0] = real_time/10;
	road1_buffer[1] = real_time%10;
}

void set_road2_buffer(uint32_t time)
{
	uint32_t real_time = time/1000;		//time(ms), real_time(s)
	road2_buffer[0] = real_time/10;
	road2_buffer[1] = real_time%10;
}

//this function is used to scanning 7seg led automatically
void sevenSegAuto()
{
	//timer3 is used to scanning led
	if(timer3_flag == 1){
		//change which led is turn on, range 0->3
		led_scanning = (led_scanning + 1) % 4;
		setTimer3(SCANNING_TIME);
	}

	switch(led_scanning)
	{
	//case n -> led n turned on
	//road1 buffer -> led 0 and 1
	//road2 buffer -> led 2 and 3
	case 0:
		display7SEG(road1_buffer[0]);
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
		break;
	case 1:
		display7SEG(road1_buffer[1]);
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
		break;
	case 2:
		display7SEG(road2_buffer[0]);
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
		break;
	case 3:
		display7SEG(road2_buffer[1]);
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
		break;
	default:
		break;
	}
}

//Auto count down every 1 second
//and change the buffer
//timer4 is used to check every 1 second
void updateBufferAuto()
{
	if(timer4_flag == 1){
		setTimer4(1000);
		//decrease time in buffer by 1
		if(road1_buffer[1] == 0){
			road1_buffer[1] = 9;
			road1_buffer[0]--;
		}
		else road1_buffer[1]--;


		if(road2_buffer[1] == 0){
			road2_buffer[1] = 9;
			road2_buffer[0]--;
		}
		else road2_buffer[1]--;
	}
}

//all buffer is set to 8 and remain unchange
void update_buffer_when_error()
{
	road1_buffer[0] = 8;
	road1_buffer[1] = 8;
	road2_buffer[0] = 8;
	road2_buffer[1] = 8;
}

//blink all red led with f = 2Hz
//make use of timer 5
void red_blink()
{
	HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, GPIO_PIN_SET);
	if(timer5_flag == 1){
		HAL_GPIO_TogglePin(RED1_GPIO_Port, RED1_Pin);
		HAL_GPIO_TogglePin(RED2_GPIO_Port, RED2_Pin);
		setTimer5(250);
	}
}

//blink all green led with f = 2Hz
//make use of timer5
void green_blink()
{
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, GPIO_PIN_SET);
	if(timer5_flag == 1){
		HAL_GPIO_TogglePin(GREEN1_GPIO_Port, GREEN1_Pin);
		HAL_GPIO_TogglePin(GREEN2_GPIO_Port, GREEN2_Pin);
		setTimer5(250);
	}
}

//blink all yellow led with f = 2Hz
//make use of timer5
void yellow_blink()
{
	HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_SET);
	if(timer5_flag == 1){
		HAL_GPIO_TogglePin(YELLOW1_GPIO_Port, YELLOW1_Pin);
		HAL_GPIO_TogglePin(YELLOW2_GPIO_Port, YELLOW2_Pin);
		setTimer5(250);
	}
}

//2 seven seg led on road 1 display time
//		....	     road 2 display mode
//this function is called in 3 manual state in fsm
void update_buffer_manual(uint8_t mode, uint32_t time)
{
	uint32_t real_time = time/1000;

	road1_buffer[0] = 0;
	road1_buffer[1] = mode;

	road2_buffer[0] = real_time/10;
	road2_buffer[1] = real_time%10;
}
//use when error occur
void turn_all_led_on()
{
	HAL_GPIO_WritePin(GPIOB, RED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GREEN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, YELLOW1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, RED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GREEN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, YELLOW2_Pin, GPIO_PIN_RESET);
}
