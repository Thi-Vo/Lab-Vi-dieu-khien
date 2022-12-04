/*
 * software_timer.h
 *
 *  Created on: Nov 13, 2022
 *      Author: DLCH
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer1_flag;
extern int timer2_flag;
extern int timer3_flag;
extern int timer4_flag;
extern int timer5_flag;

extern const int TIMER_CYCLE;

void timerRun();

void setTimer1(uint32_t duration);
void setTimer2(uint32_t duration);
void setTimer3(uint32_t duration);
void setTimer4(uint32_t duration);
void setTimer5(uint32_t duration);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern uint8_t real_time;
#endif /* INC_SOFTWARE_TIMER_H_ */
