/*
 * task.c
 *
 *  Created on: Dec 3, 2022
 *      Author: DLCH
 */

#ifndef SRC_TASK_C_
#define SRC_TASK_C_

#include "task.h"
#include "software_timer.h"
#include "stdio.h"


#define MAX_BUFFER_SIZE  30
uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
void first_uart_call()
{
	HAL_UART_Receive_IT(&huart2, &temp, 1);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){
		HAL_UART_Transmit(&huart2, &temp, 1, 500);
		buffer[index_buffer++] = temp;
		if(index_buffer >= 30) index_buffer = 0;

		buffer_flag = 1;
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}

#endif /* SRC_TASK_C_ */
