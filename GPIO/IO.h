/*
 * AVR_io.h
 *
 * Created: 10/15/2021 3:24:45 AM
 *  Author: Ali Shabana
 */ 


#ifndef AVR_IO_H_
#define AVR_IO_H_

#include "../utilities/std_types.h"
#include "../utilities/bit_mask.h"


typedef enum {
	PIN_0 = 0,
	PIN_1 = 1,
	PIN_2 = 2,
	PIN_3 = 3,
	PIN_4 = 4,
	PIN_5 = 5,
	PIN_6 = 6,
	PIN_7 = 7,
	}IO_pin_number_t;
	
typedef enum{
	GROUPA = 1,
	GROUPB = 2,
	GROUPC = 3,
	GROUPD = 4,
	}IO_pin_group_t;
	

typedef enum{
	LOW = 0,
	HIGH = 1,
	}IO_pin_data_t;

typedef enum{
	INPUT = 0,
	OUTPUT = 1,
	}IO_pin_direction_t;



void IO_set_pin_direction(IO_pin_group_t group, IO_pin_number_t pin, IO_pin_direction_t dir);

void IO_set_pin_data(IO_pin_group_t group, IO_pin_number_t pin, IO_pin_data_t data);

IO_pin_data_t IO_get_pin_data(IO_pin_group_t group, IO_pin_number_t pin);

void IO_set_group_direction(IO_pin_group_t group, u8_t group_direction);

void IO_set_group_data(IO_pin_group_t group, u8_t group_data);

u8_t IO_get_group_data(IO_pin_group_t group);



#endif /* AVR_IO_H_ */