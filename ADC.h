/*
 * ADC.h
 *
 * Created: 18.03.2021 13:08:47
 *  Author: Andreas Knutli
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define diodeA ADC_MUXPOS_AIN0_gc
#define diodeB ADC_MUXPOS_AIN1_gc
#define diodeC ADC_MUXPOS_AIN2_gc
#define diodeD ADC_MUXPOS_AIN3_gc

void ADC_init(void);

uint16_t ADC_read(uint8_t diode);

#endif /* ADC_H_ */