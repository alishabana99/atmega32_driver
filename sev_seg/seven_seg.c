/*
 * seven_seg.c
 *
 * Created: 10/23/2021 12:04:04 PM
 *  Author: Florida
 */ 

#include "seven_seg.h"


const unsigned char _7seg_lookup[10] = {
	0b0111111,
	0b0000110,
	0b1011011,
	0b1001111,
	0b1100110,
	0b1101101,
	0b1111101,
	0b0000111,
	0b1111111,
	0b1101111,
};


void SEV_SEG_init(SEV_SEG_config_t sev_seg){

	IO_set_group_direction(sev_seg.seven_seg_pins_group,0xff);	
	
}
void SEV_SEG_print_number(SEV_SEG_config_t sev_seg, u8_t num){
	
	u8_t sev_seg_num = _7seg_lookup[num];
	IO_set_group_data(sev_seg.seven_seg_pins_group,sev_seg_num);
	
}