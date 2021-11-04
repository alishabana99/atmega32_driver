/*
 * bit_mask.h
 *
 * Created: 10/15/2021 3:40:53 AM
 *  Author: Florida
 */ 


#ifndef BIT_MASK_H_
#define BIT_MASK_H_

//FOR THE SAKE OF IO driver 
#define  UPDATE_BIT(reg,bit,lvl)    if(lvl){\
	SET_BIT(reg,bit);\
}\
else{\
	CLEAR_BIT(reg,bit);\
}

#define  SET_BIT(reg,bit)		reg |= (1<<bit)
#define  CLEAR_BIT(reg,bit)		reg &= ~(1<<bit)
#define  TOGGLE_BIT(reg,bit)	reg ^= (1<<bit)
#define  GET_BIT(reg,bit)		bit = (reg>>bit)& 1

//#define GET_BIT(REG,BIT) ((REG & (1<<BIT)) >> BIT)



#endif /* BIT_MASK_H_ */