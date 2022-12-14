/*
 * fsm.h
 *
 *  Created on: Dec 3, 2022
 *      Author: DLCH
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "task.h"

extern ADC_HandleTypeDef hadc1;
void cmd_parser_fsm();
void uart_communication_fsm();

#endif /* INC_FSM_H_ */
