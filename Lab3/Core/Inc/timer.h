/*
 * timer.h
 *
 *  Created on: Oct 14, 2022
 *      Author: DLCH
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "global_variable.h"

extern int timer1_flag;
extern int timer2_flag;
extern int timer3_flag;
extern int timer4_flag;
extern int timer5_flag;

void timerRun();

void setTimer1(uint32_t duration);
void setTimer2(uint32_t duration);
void setTimer3(uint32_t duration);
void setTimer4(uint32_t duration);
void setTimer5(uint32_t duration);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#endif /* INC_TIMER_H_ */
