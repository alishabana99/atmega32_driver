/*
 * seven_seg.h
 *
 * Created: 10/23/2021 12:03:53 PM
 *  Author: Florida
 */ 


#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_

#include "../utilities/std_types.h"
#include "../GPIO//IO.h"



typedef struct {
	IO_pin_group_t seven_seg_pins_group;
		
	}SEV_SEG_config_t;

void SEV_SEG_init(SEV_SEG_config_t sev_seg);
void SEV_SEG_print_number(SEV_SEG_config_t sev_seg, u8_t num);

#endif /* SEVEN_SEG_H_ */