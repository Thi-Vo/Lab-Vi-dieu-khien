/*
 * fsm.c
 *
 *  Created on: Dec 3, 2022
 *      Author: DLCH
 */
#include "main.h"
#include "software_timer.h"
#include "fsm.h"
#include "task.h"
#include "stdio.h"

ADC_HandleTypeDef hadc1;
enum status state = INIT;
int adc_value;
uint8_t uart_flag = 0;
char str[100];

/*
 * !RST# -> send data
 * !OK#  -> stop
 * if !RST#, send every 3s until !OK#
*/
void cmd_parser_fsm()
{
	switch(state)
	{
	case INIT:
		if(temp == '!') state = BEGIN;
		break;
	case BEGIN:
		if(temp == 'R') state = R;
		else if(temp == 'O') state = O;
		else if(temp == '!') {}
		else state = INIT;
		break;
	case R:
		if(temp == 'S') state = S;
		else if(temp == '!') state = BEGIN;
		else state = INIT;
		break;
	case S:
		if(temp == 'T') state = T;
		else if(temp == '!') state = BEGIN;
		else state = INIT;
		break;
	case T:
		if(temp == '#') {
			state = INIT;
			uart_flag = 1;
			setTimer1(3000);
		}
		else if(temp == '!') state = BEGIN;
		else state = INIT;
		break;
	case O:
		if(temp == 'K') state = K;
		else if(temp == '!') state = BEGIN;
		else state = INIT;
		break;
	case K:
		if(temp == '#') {
			state = INIT;
			reset_timer1();
		}
		else if(temp == '!') state = BEGIN;
		else state = INIT;
		break;
	default:
		break;
	}
}
void uart_communication_fsm()
{
	if(uart_flag == 1)
	{
		adc_value = HAL_ADC_GetValue(&hadc1);
		sprintf(str, "\r!ADC=%d#\r", adc_value);
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 3000);
		uart_flag = 0;
	}
	if(timer1_flag == 1){
		setTimer1(3000);
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 3000);
	}
}

