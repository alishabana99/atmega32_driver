/*
 * keypad.c
 *
 * Created: 10/20/2021 4:46:35 PM
 *  Author: Florida
 */ 
#include "../GPIO/IO.h"
#include "../utilities/std_types.h"
#include "keypad.h"
#include "../LCD_hd44780/lcd_hd44780.h"

#include "../sev_seg/seven_seg.h"

#ifndef F_CPU
#define  F_CPU 1000000UL
#endif
#include <util/delay.h>


static int KEYPAD_structure[4][3] = 
	{
		{
			'1','2','3'
		},
		{
			'4','5','6'
		},
		{
			'7','8','9'
		},
		{
			'*','0','#'
		},
	};


void KEYPAD_init(KEYPAD_config_t config){
	
	//rows-> (0-3 pins) are output     
	//columns-> (4-7 pins) are input
	IO_set_group_direction(config.keypad_pins_group,0x0f);
	
	//rows-> (0-3 pins) are ZEROed
	//columns-> (4-7 pins) are ONEed to enable the internal pull-up resistance
	IO_set_group_data(config.keypad_pins_group,0xff);
	
	
}

u8_t KEYPAD_get_pressed_key(KEYPAD_config_t keypad, u8_t* pressed_key){
	
	u8_t row = 0;
	u8_t col = 0;
	u8_t result = 0x00;
	
	
	for (row =0 ;row< keypad.rows_number ; row++)
	{
		
		IO_set_group_data(keypad.keypad_pins_group,(~(0x01<< row)));
		
		
		for(col =0;col< keypad.cols_number ; col++){
			
			result |= (~(0x01 <<row)) ; 
			
			
			if(IO_get_pin_data(keypad.keypad_pins_group, col+4) == LOW){   //means it has an input, because its pull-up resistance works
				//LCD_clear();
				_delay_ms(20);
				
				result |= (1<<(col+4));
				_delay_ms(20);
				
				//LCD_clear();
				*pressed_key =  KEYPAD_structure[row][col];
				return 1;
				
			}else{
									
			}
			
			
			    _delay_ms(10);

			
		}
	}
	
	//none was clicked 
	return 0;
}



u8_t scanning(KEYPAD_config_t keypad){

	
		_delay_ms(20);
		
		IO_set_group_data(keypad.keypad_pins_group,0b11111110);
		_delay_ms(20);
		
		u8_t result = IO_get_group_data(keypad.keypad_pins_group);
		_delay_ms(20);
		result &= 0xf0;
		_delay_ms(20);
		
		
		LCD_string_write((u8_t*)"result = ");
		LCD_char_write((u8_t)result);
		_delay_ms(1000);
		LCD_clear();
		// --- row 0 ------
		if (result == 0b11100000)
		{
			return '1';
		}
		
			_delay_ms(10);

			
	
	
	//none was clicked
	return '$';
	
}