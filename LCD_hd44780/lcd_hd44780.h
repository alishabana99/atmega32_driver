/*
 * lcd_hd44780.h
 *
 * Created: 10/19/2021 6:25:28 PM
 *  Author: Florida
 */ 


#ifndef LCD_HD44780_H_
#define LCD_HD44780_H_

/*
enum used in traveling between LCD lines
*/
typedef enum  {
	FIRST_LINE =1,
	SECOND_LINE =2,
} LCD_line;

/*
enum used in specifying the writing mode (while moving to a line, would you like to overwrite the previous data, or continue from left off
*/
typedef enum {
	overwrite = 1,
	concatenate
}LCD_typing_mode;

/*
enum used in specifying the direction of display shift    (used in LCD_display_shift() function)
*/
typedef enum{
	shift_right = 0,
	shift_left = 1,
	}LCD_display_shift_dir_t;
	
/*
enum used as a flag for whether characters exceeded the 16-column space visible on the LCD, if so, the "display shifting" function would be get into work
*/
typedef enum{
	not_exceeded = 0,
	exceeded = 1,
	}LCD_exceeded_screen_t;
	
//used for the same reason of the above enum    --> LCD_exceeded_screen_t
extern LCD_exceeded_screen_t screen_space;

//Connections pins settings
#define  LCD_data_group	GROUPB 
#define	 LCD_ctrl_group GROUPD
#define  LCD_rs 0
#define  LCD_rw 1
#define  LCD_en 2



void LCD_init();

void LCD_cmd_write(unsigned char cmd);

void LCD_gotoLine(LCD_line line_number,LCD_typing_mode mode);

void LCD_char_write(unsigned char c);

void LCD_string_write(u8_t* str);

void LCD_display_shift(LCD_display_shift_dir_t shift_dir);

void LCD_clear();




#endif /* LCD_HD44780_H_ */