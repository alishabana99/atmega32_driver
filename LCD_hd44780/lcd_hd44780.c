/*
 * lcd_hd44780.c
 *
 * Created: 10/19/2021 6:35:11 PM
 *  Author: Florida
 */ 


#include "../GPIO/IO.h"
#include "../utilities/std_types.h"
#include "lcd_hd44780.h"

#include <string.h>



#ifndef F_CPU
#define  F_CPU 1000000UL
#endif
#include <util/delay.h>

//Instructions
#define LCD_clear_display 0x01
#define LCD_return_home 0x02
//       ---entry mode variations---
#define LCD_entry_mode_cursor_inc_display_shift 0x07
#define LCD_entry_mode_cursor_inc				0x06
#define LCD_entry_mode_cursor_dec_display_shift 0x05
#define LCD_entry_mode_cursor_dec				0x04
//		---display control variations---display ON
#define LCD_display_on_cursor_on_blinking_on    0x0f
#define LCD_display_on_cursor_on_blinking_off	0x0e
#define LCD_display_on_cursor_off_blinking_on   0x0d
#define LCD_display_on_cursor_off_blinking_off  0x0c
//                                      display OFF
#define LCD_display_off_cursor_on_blinking_on   0x0b
#define LCD_display_off_cursor_on_blinking_off  0x0a
#define LCD_display_off_cursor_off_blinking_on  0x09
#define LCD_display_off_cursor_off_blinking_off 0x08

#define LCD_function_set_8bit_2lines_5_10font	0x3c
//      ---display/cursor shift (right/left) variation---
#define LCD_display_right_shift					0x1c
#define LCD_display_left_shift					0x18
#define LCD_cursor_right_shift					0x14
#define LCD_cursor_left_shift					0x10

#define LCD_first_line						    0x80
#define LCD_second_line						    0xC0
//END of instructions



/*
	these indicators are used to save witting positions for each line. in order to be continued later,
	 we've 2 writing modes [Concatenating, Overwriting] 
 */
static LCD_line current_line = FIRST_LINE;
static u8_t first_line_indicator = 0;
static u8_t second_line_indicator = 0;
static u8_t* indicator =&first_line_indicator;


/*
a global variable that is used as a flag for the data on the LCD if exceeded the-16-column space 
-> so, display begin to do shifts revealing the hiddent content.
*/
LCD_exceeded_screen_t screen_space = not_exceeded;




void LCD_cmd_write(unsigned char cmd){
	//putting the cmd on the bus
	IO_set_group_data(LCD_data_group,cmd);
	//configuring the select[RS] and read/write[rw] pins
	IO_set_pin_data(LCD_ctrl_group,LCD_rs,LOW);
	IO_set_pin_data(LCD_ctrl_group,LCD_rw,LOW);
	//setting enable to be reseted later to give
	IO_set_pin_data(LCD_ctrl_group,LCD_en,HIGH);
	_delay_ms(10);
	IO_set_pin_data(LCD_ctrl_group,LCD_en,LOW);
	_delay_ms(10);
}

void LCD_gotoLine(LCD_line line_number,LCD_typing_mode mode){
	switch (line_number)
	{
		case FIRST_LINE:
		second_line_indicator = (*indicator);    //saving main indicator's state (its position in the second line) to be retrieved later. 
		indicator = &first_line_indicator;       //switching the main indicator to the first line 
		current_line = FIRST_LINE;
		
		//if the writing mode is : overwrite, so we reset the indicator to 0(the first position in the line) where it starts to create new data
		if (mode == overwrite)				
		{
			first_line_indicator = 0;			
			}else{
			
		}
		
		//putting the indicator in the first line (first place+ the number of positions it was previously traveled)
		//it will be 0, if the writing mode is: overwrite   --> so we put the indicator at the beginning of the 1st line
		LCD_cmd_write(LCD_first_line + (*indicator));
		break;
		
		case SECOND_LINE:
		first_line_indicator = (*indicator);   //saving main indicator's state (its position in the first line) to be retrieved later.
		indicator = &second_line_indicator;    //switching the main indicator to the second line
		current_line = SECOND_LINE;
		
		//if the writing mode is : overwrite, so we reset the indicator to 0(the first position in the line) where it starts to create new data
		if (mode == overwrite)   
		{
			second_line_indicator = 0;
			}else{
			
		}
		
		 //putting the indicator in the second line (first place+ the number of positions it was previously traveled)
		 //it will be 0, if the writing mode is: overwrite   --> so we put the indicator at the beginning of the 2nd line
		LCD_cmd_write(LCD_second_line + (*indicator));     
		break;
		default:
		
		break;
	}
}



void LCD_char_write(unsigned char c){

	//indicator-increasing logic 
	//FOR GotoLine function 
	
	if((*indicator) < 40){  //each line has 40 character addresses  (only 16 of them appears on screen)
		(*indicator)++;
		}else{
		return; //i don't want to overwrite any text
	}
	
	//checking if the screen is now full of the characters, so assign the exceeded flag, in order to be checked later to enable the display shifting action (in the main)/
	if((*indicator > 16)){
		screen_space = exceeded;
	}else{
		
	}


	//putting the data to the data bus
	IO_set_group_data(LCD_data_group, c);
	_delay_ms(20);
	//configuring select, read/write pins and enable pins  [src: datasheet]
	IO_set_pin_data(LCD_ctrl_group,LCD_rs,HIGH);
	IO_set_pin_data(LCD_ctrl_group,LCD_rw,LOW);
	IO_set_pin_data(LCD_ctrl_group,LCD_en,HIGH);
	//waiting for the setup time : for stability
	_delay_ms(10);
	//a high-to-low pulse in order for the LCD to latch in the data present at the data pins.
	IO_set_pin_data(LCD_ctrl_group,LCD_en,LOW);
	//waiting for the hold time : for stability
	_delay_ms(10);
	
	
	
}


void LCD_string_write(u8_t* str){
	u8_t index = 0;
	while (str[index] != '\0')
	{
		LCD_char_write (str[index]);
		index++;
		_delay_ms (5);
	}
	
	_delay_ms(100);
	
	
}


void LCD_init(){
	
	//configuring data and control group as OUTPUT -- 
	  IO_set_group_direction(LCD_data_group,0xff);
	  IO_set_pin_direction(LCD_ctrl_group,LCD_rs,OUTPUT);
	  IO_set_pin_direction(LCD_ctrl_group,LCD_rw,OUTPUT);
	  IO_set_pin_direction(LCD_ctrl_group,LCD_en,OUTPUT);
	  
	  
	_delay_ms(40);   //necessary delay after LCD power on
	LCD_cmd_write(LCD_function_set_8bit_2lines_5_10font);
	_delay_ms(10);
	LCD_cmd_write(LCD_function_set_8bit_2lines_5_10font);
	_delay_ms(20);
	LCD_cmd_write(LCD_function_set_8bit_2lines_5_10font);
	//from here we can work with the busy flag instead of delays
	LCD_cmd_write(LCD_display_on_cursor_on_blinking_on);
	LCD_cmd_write(LCD_clear_display);
	LCD_cmd_write(LCD_entry_mode_cursor_inc);
	
}


void LCD_display_shift(LCD_display_shift_dir_t shift_dir){
	switch (shift_dir)
	{
	case shift_left:
		LCD_cmd_write(LCD_display_left_shift);
		break;
	case shift_right:
		LCD_cmd_write(LCD_display_right_shift);
		break;
	default:{
		
	}
	}
}


void LCD_clear(){
	LCD_cmd_write(LCD_clear_display);
	LCD_cmd_write(LCD_return_home);
	(*indicator) = 0;
}


