/*
 * keypad.h
 *
 * Created: 10/20/2021 4:46:50 PM
 *  Author: Florida
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_


	
	typedef struct {
		u8_t rows_number;
		u8_t cols_number;
		IO_pin_group_t keypad_pins_group;
	}KEYPAD_config_t;


void KEYPAD_init(KEYPAD_config_t config);

u8_t KEYPAD_get_pressed_key(KEYPAD_config_t keypad, u8_t* pressed_key);


u8_t scanning(KEYPAD_config_t keypad);


#endif /* KEYPAD_H_ */