/*
 * task.h
 *
 *  Created on: Dec 3, 2022
 *      Author: DLCH
 */

#ifndef INC_TASK_H_
#define INC_TASK_H_

#include "main.h"

extern uint8_t buffer_flag;

void first_uart_call();

enum status{
	INIT = 0,
	BEGIN = 1,
	R = 3,
	S = 4,
	T = 5,
	O = 7,
	K = 8

};

extern uint8_t temp;
#endif /* INC_TASK_H_ */
