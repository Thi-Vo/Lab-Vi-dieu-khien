/*
 * scheduler.c
 *
 *  Created on: Nov 13, 2022
 *      Author: DLCH
 */

#include "main.h"
#include "software_timer.h"
#include "scheduler.h"
#include "string.h"
#include "stdio.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;


void SCH_Add_Task ( void (*pFunction)() , uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task < SCH_MAX_TASKS){
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY/TIMER_CYCLE;
		SCH_tasks_G[current_index_task].Period =  PERIOD/TIMER_CYCLE;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;

		current_index_task++;
	}
}

void SCH_Update(void){
	for(int i = 0; i < current_index_task; i++){
		if(SCH_tasks_G[i].pTask == 0x0000) continue;
		if (SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay --;
		}else{
			SCH_tasks_G[i].RunMe += 1;
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
		}
	}
}

void SCH_Dispatch_Tasks(void){
	for(int i = 0; i < current_index_task; i++){
		if(SCH_tasks_G[i].pTask != 0 && SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();
			if(SCH_tasks_G[i].Period == 0) SCH_Delete_Task(i);
		}
	}
}


void SCH_Delete_Task(uint32_t index){
    if (SCH_tasks_G[index].pTask == 0) {
    	return;
    }
    SCH_tasks_G[index].pTask = 0x0000;
    SCH_tasks_G[index].Delay = 0;
    SCH_tasks_G[index].Period = 0;
    SCH_tasks_G[index].RunMe = 0;
    return;
}





//task is defined from here
UART_HandleTypeDef huart2;
//time stamp is stored here
char buf_time[3];
char red_call[] = " : Toggle red\r";
char yellow_call[] = " : Toggle yellow\r";
char green_call[] = " : Toggle green\r";
char white_call[] = " : Toggle white\r";
char pink_call[] = " : Toggle pink\r";

//toggle red led and send string via uart
//the same behavior for other functions
void red()
{
	HAL_GPIO_TogglePin(GPIOA, RED_Pin);
	sprintf(buf_time, "%d",real_time);
	HAL_UART_Transmit(&huart2, (uint8_t*)buf_time,strlen(buf_time) , 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)red_call, sizeof(red_call), 2000);
}

void yellow()
{
	HAL_GPIO_TogglePin(GPIOA, YELLOW_Pin);
	sprintf(buf_time, "%d",real_time);
	HAL_UART_Transmit(&huart2, (uint8_t*)buf_time,strlen(buf_time) , 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)yellow_call, sizeof(yellow_call), 2000);
}

void green()
{
	HAL_GPIO_TogglePin(GPIOA, GREEN_Pin);
	sprintf(buf_time, "%d",real_time);
	HAL_UART_Transmit(&huart2, (uint8_t*)buf_time,strlen(buf_time) , 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)green_call, sizeof(green_call), 2000);
}

void white()
{
	HAL_GPIO_TogglePin(GPIOA, WHITE_Pin);
	sprintf(buf_time, "%d",real_time);
	HAL_UART_Transmit(&huart2, (uint8_t*)buf_time,strlen(buf_time) , 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)white_call, sizeof(white_call), 2000);
}

void pink()
{
	HAL_GPIO_TogglePin(GPIOA, PINK_Pin);
	sprintf(buf_time, "%d",real_time);
	HAL_UART_Transmit(&huart2, (uint8_t*)buf_time,strlen(buf_time) , 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)pink_call, sizeof(pink_call), 2000);
}
