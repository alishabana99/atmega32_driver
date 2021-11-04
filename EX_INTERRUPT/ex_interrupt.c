/*
 * ex_interrupt.c
 *
 * Created: 11/2/2021 1:41:13 PM
 *  Author: Florida
 */ 

#include "ex_interrupt.h"

//REGISTERS ADDRESSES
//SREG
#define STATUS_reg *((volatile u8_t*) 0x5F)
#define GLOBAL_INT_EN_BIT 1

//GICR - Which external interrupt would you like to enable
#define EX_INT_CONTROL_reg *((volatile u8_t*) 0x5B)
#define EX_INT0_EN_BIT 6
#define EX_INT1_EN_BIT 7
#define EX_INT2_EN_BIT 5

//MCUCR - how do you like to sense the interrupt (INT0 -INT1)
#define EX_INT_SENSE_CONTROL_reg *((volatile u8_t*) 0x55)
#define EX_INT0_SENSE_CONTROL_BIT00 0
#define EX_INT0_SENSE_CONTROL_BIT01 1
#define EX_INT1_SENSE_CONTROL_BIT10 2
#define EX_INT1_SENSE_CONTROL_BIT11 3

//MCUCSR - how do you like to sense the interrupt (INT2)(only edge-sensitive)
#define EX_INT2_SENSE_CONTROL_reg *((volatile u8_t*) 0x45)
#define EX_INT2_SENSE_CONTROL_BIT 6

//GIFR - reading external interrupt flags 
#define EX_INT_FLAG_reg *((volatile u8_t*) 0x5A)
#define EX_INT0_FLAG_BIT 6
#define EX_INT1_FLAG_BIT 7
#define EX_INT2_FLAG_BIT 5


static void (*INT0_FuncPTR)(void) = 0;
static void (*INT1_FuncPTR)(void) = 0;
static void (*INT2_FuncPTR)(void) = 0;



void EX_INTERRUPT_enable(EX_INTERRUPT_source_type_t int_src){
	
	switch (int_src)
	{
	case EX_INT0:
		SET_BIT(EX_INT_CONTROL_reg,EX_INT0_EN_BIT);
		break;
	case EX_INT1:
		SET_BIT(EX_INT_CONTROL_reg,EX_INT1_EN_BIT);
		break;
	case EX_INT2:
		SET_BIT(EX_INT_CONTROL_reg,EX_INT2_EN_BIT);
		break;
	}
	
}

void EX_INTERRUPT_disable(EX_INTERRUPT_source_type_t int_src){
	
	switch (int_src)
	{
		case EX_INT0:
		CLEAR_BIT(EX_INT_CONTROL_reg,EX_INT0_EN_BIT);
		break;
		case EX_INT1:
		CLEAR_BIT(EX_INT_CONTROL_reg,EX_INT1_EN_BIT);
		break;
		case EX_INT2:
		CLEAR_BIT(EX_INT_CONTROL_reg,EX_INT2_EN_BIT);
		break;
	}
	
}

void EX_INTERRUPT_SET_SENSE(EX_INTERRUPT_source_type_t int_src, EX_INTERRUPT_sense_t sense){
	switch (int_src)
	{
		//EX_INT0
		case EX_INT0:
			switch (sense)
			{
			case EX_INT_LOW_LEVEL:
				CLEAR_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT0_SENSE_CONTROL_BIT00);
				CLEAR_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT0_SENSE_CONTROL_BIT01);
				break;
			case EX_INT_ANY_LOGIC_CHANGE:
				SET_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT0_SENSE_CONTROL_BIT00);
				CLEAR_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT0_SENSE_CONTROL_BIT01);
				break;
			case EX_INT_FALLING_EDGE:
				CLEAR_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT0_SENSE_CONTROL_BIT00);
				SET_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT0_SENSE_CONTROL_BIT01);
				break;
			case EX_INT_RISING_EDGE:
				SET_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT0_SENSE_CONTROL_BIT00);
				SET_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT0_SENSE_CONTROL_BIT01);
				break;
			}
		break;
		
		//EX_INT1
		case EX_INT1:
			switch(sense)
			{
				case EX_INT_LOW_LEVEL:
					CLEAR_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT1_SENSE_CONTROL_BIT10);
					CLEAR_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT1_SENSE_CONTROL_BIT11);
					break;
				case EX_INT_ANY_LOGIC_CHANGE:
					SET_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT1_SENSE_CONTROL_BIT10);
					CLEAR_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT1_SENSE_CONTROL_BIT11);
					break;
				case EX_INT_FALLING_EDGE:
					CLEAR_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT1_SENSE_CONTROL_BIT10);
					SET_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT1_SENSE_CONTROL_BIT11);
					break;
				case EX_INT_RISING_EDGE:
					SET_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT1_SENSE_CONTROL_BIT10);
					SET_BIT(EX_INT_SENSE_CONTROL_reg,EX_INT1_SENSE_CONTROL_BIT11);
					break;
			}
		break;
		
		
		//EX_INT2
		case EX_INT2:
			switch (sense)
			{
			case EX_INT_FALLING_EDGE:
				CLEAR_BIT(EX_INT2_SENSE_CONTROL_reg,EX_INT2_SENSE_CONTROL_BIT);
				break;
			case EX_INT_RISING_EDGE:
				SET_BIT(EX_INT2_SENSE_CONTROL_reg,EX_INT2_SENSE_CONTROL_BIT);
				break;
			default:
				//FALLING EDGE is the default behavior
				CLEAR_BIT(EX_INT2_SENSE_CONTROL_reg,EX_INT2_SENSE_CONTROL_BIT);
			}
	}
		
}

void EX_INTERRUPT_SET_CALLBACK(EX_INTERRUPT_source_type_t int_src,void (*localFuncPTR)(void)){
	
	switch (int_src)
	{
	case EX_INT0:
		INT0_FuncPTR = localFuncPTR;
		break;
	case EX_INT1:
		INT1_FuncPTR = localFuncPTR;
		break;
	case EX_INT2: 
		INT2_FuncPTR = localFuncPTR;
		break;
	}
	
}

/************************************************************************/
/*                                ISRs                                  */
/************************************************************************/
ISR(INT0_vect)
{
	if (INT0_FuncPTR != 0)
	{
		INT0_FuncPTR();
	}
}
ISR(INT1_vect)
{
	if (INT1_FuncPTR!=0)
	{
		INT0_FuncPTR();
	}
}
ISR(INT2_vect)
{
	if (INT2_FuncPTR!=0)
	{
		INT2_FuncPTR();
	}
}