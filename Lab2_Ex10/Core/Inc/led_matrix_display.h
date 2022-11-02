/*
 * led_matrix_display.h
 *
 *  Created on: 12 Oct 2022
 *      Author: DLCH
 */

#ifndef INC_LED_MATRIX_DISPLAY_H_
#define INC_LED_MATRIX_DISPLAY_H_

#include "main.h"
#include "string.h"
//uint8_t set_col_off[8] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};

extern char buffer[8];

int get_bit(uint8_t ,int);
void set_row_on(int num);
void set_row_off();
void display_char();
void write_data(int position);
void display_string(char* str);
void update_buffer(char c);

#endif /* INC_LED_MATRIX_DISPLAY_H_ */
