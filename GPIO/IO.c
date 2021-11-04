/*
 * AVR_io.c
 *
 * Created: 10/15/2021 3:27:40 AM
 *  Author: Ali Shabana
 */ 

#include "../utilities/std_types.h"
#include "../utilities/bit_mask.h"
#include "IO.h"

#define DDRA_reg	*((volatile u8_t*)	0x3a)
#define PORTA_reg	*((volatile u8_t*)	0x3b)
#define PINA_reg	*((volatile u8_t*)	0x39)

#define DDRB_reg	*((volatile u8_t*)	0x37)
#define PORTB_reg	*((volatile u8_t*)	0x38)
#define PINB_reg	*((volatile u8_t*)	0x36)

#define DDRC_reg	*((volatile u8_t*)	0x34)
#define PORTC_reg	*((volatile u8_t*)	0x35)
#define PINC_reg	*((volatile u8_t*)	0x33)

#define DDRD_reg	*((volatile u8_t*)	0x31)
#define PORTD_reg	*((volatile u8_t*)	0x32)
#define PIND_reg	*((volatile u8_t*)	0x30)



void IO_set_pin_direction(IO_pin_group_t group, IO_pin_number_t pin, IO_pin_direction_t dir){
	
	switch (group)
	{
	case GROUPA:
		UPDATE_BIT(DDRA_reg,pin,dir);
		break;
	case GROUPB:
		UPDATE_BIT(DDRB_reg,pin,dir);
		break;
	case GROUPC:
		UPDATE_BIT(DDRC_reg,pin,dir);
		break;
	case GROUPD:
		UPDATE_BIT(DDRD_reg,pin,dir);
		break;
	default:{
		
	}
	
	}
}


void IO_set_pin_data(IO_pin_group_t group, IO_pin_number_t pin, IO_pin_data_t data){
	switch (group)
	{
	case GROUPA:
		UPDATE_BIT(PORTA_reg,pin,data);
		break;
		
	case GROUPB:
		UPDATE_BIT(PORTB_reg,pin,data);
		break;
	
	case GROUPC:
		UPDATE_BIT(PORTC_reg,pin,data);
		break;
		
	case GROUPD:
		UPDATE_BIT(PORTD_reg,pin,data);
		break;
	default:{
		
	}
	
	}
}

IO_pin_data_t IO_get_pin_data(IO_pin_group_t group, IO_pin_number_t pin){
	IO_pin_data_t pin_lvl = LOW; //just an initial value
	
	switch(group){
		case GROUPA:
			pin_lvl= GET_BIT(PINA_reg,pin);
			break;
		case GROUPB:
			pin_lvl= GET_BIT(PINB_reg,pin);
			break;
		case GROUPC:
			pin_lvl= GET_BIT(PINC_reg,pin);
			break;
		case GROUPD:
			pin_lvl= GET_BIT(PIND_reg,pin);
			break;
		default:{
			
		}
	
	}
	
	return pin_lvl;
}

void IO_set_group_direction(IO_pin_group_t group, u8_t group_direction){
	
	switch (group)
	{
	case GROUPA:
			DDRA_reg = group_direction;
			break;
	
	case GROUPB:
		DDRB_reg = group_direction;
		break;
	
	case GROUPC:
		DDRC_reg = group_direction;
		break;
	
	case GROUPD:
		DDRD_reg = group_direction;
		break;
	default:{
		
		}
	}
}

void IO_set_group_data(IO_pin_group_t group, u8_t group_data){
	switch (group)
	{
	case GROUPA:
		PORTA_reg = group_data;
		break;
	case GROUPB:
		PORTB_reg = group_data;
		break;
	case GROUPC:
		PORTC_reg = group_data;
		break;
	case GROUPD:
		PORTD_reg = group_data;
		break;
	default:{
		
	}
	}
}

u8_t IO_get_group_data(IO_pin_group_t group){
	u8_t grp_lvl = 0x00;
	
	switch (group)
	{
	case GROUPA:
		grp_lvl = PINA_reg;
		break;
	
	case GROUPB:
		grp_lvl = PINB_reg;
		break;
	
	case GROUPC:
		grp_lvl = PINC_reg;
		break;
	
	case GROUPD:
		grp_lvl = PIND_reg;
		break;
	
	default:{

		}
	}
	
	return grp_lvl;
}