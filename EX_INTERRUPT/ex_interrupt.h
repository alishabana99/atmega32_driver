/*
 * ex_interrupt.h
 *
 * Created: 11/2/2021 1:41:33 PM
 *  Author: Florida
 */ 


#ifndef EX_INTERRUPT_H_
#define EX_INTERRUPT_H_

#include "../utilities/std_types.h"
#include "../utilities/bit_mask.h"


//Because I'll Use it in main()
#define STATUS_reg *((volatile u8_t*) 0x5F)
#define GLOBAL_INT_EN_BIT 1

//assembly instructions that will be needed
#define sei()  __asm__ __volatile__ ("sei" ::)    //sets the global interrupt enable bit
#define cli()  __asm__ __volatile__ ("cli" ::)    //clears the global interrupt enable bit 
#define reti()  __asm__ __volatile__ ("reti" ::)  



#define ISR(vector,...)\
void vector() __attribute__ ((signal)) __VA_ARGS__;\
void vector()


/* External Interrupt Request 0 */
#define INT0_vect			__vector_1
/* External Interrupt Request 1 */
#define INT1_vect			__vector_2
/* External Interrupt Request 2 */
#define INT2_vect			__vector_3
/* Timer/Counter2 Compare Match */



typedef enum {
	EX_INT0 = 0,
	EX_INT1 = 1,
	EX_INT2 = 2,
	}EX_INTERRUPT_source_type_t;
	
typedef enum {
	EX_INT_LOW_LEVEL = 0,
	EX_INT_ANY_LOGIC_CHANGE,
	EX_INT_FALLING_EDGE, 
	EX_INT_RISING_EDGE,
	}EX_INTERRUPT_sense_t;
	
//Initialization

//enable
void EX_INTERRUPT_enable(EX_INTERRUPT_source_type_t int_src);
//disable
void EX_INTERRUPT_disable(EX_INTERRUPT_source_type_t int_src);

void EX_INTERRUPT_SET_SENSE(EX_INTERRUPT_source_type_t int_src, EX_INTERRUPT_sense_t sense);

void EX_INTERRUPT_SET_CALLBACK(EX_INTERRUPT_source_type_t int_src,void (*localFuncPTR)(void));

#endif /* EX_INTERRUPT_H_ */