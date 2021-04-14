/*
 * ADC.h
 *
 * Created: 18.03.2021 13:08:47
 *  Author: Andreas Knutli
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

typedef enum{
	DIODE_A = ADC_MUXPOS_AIN0_gc,
	DIODE_B = ADC_MUXPOS_AIN1_gc,
	DIODE_C = ADC_MUXPOS_AIN2_gc,
	DIODE_D = ADC_MUXPOS_AIN3_gc
	} diode_t;

void ADC_init(void);

uint16_t ADC_read(diode_t diode);

#endif /* ADC_H_ */