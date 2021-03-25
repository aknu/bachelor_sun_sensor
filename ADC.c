/*
 * ADC.c
 *
 * Created: 18.03.2021 12:18:35
 *  Author: Andreas Knutli
 */ 

#include "ADC.h"
#include <avr/io.h>

void ADC_init(void)
	{
		VREF.ADC0REF = VREF_REFSEL_4V096_gc;	//Set VREF to 2,5V
		ADC0.CTRLC = ADC_PRESC_DIV20_gc;		//Select pre-scaler to 20 (CLK_ADC = 4Mhz/20 = 200kHz)
		ADC0.CTRLA = ADC_ENABLE_bm;				//Enable ADC
	}
	
uint16_t ADC_read(uint8_t diode)
	{
		ADC0.MUXPOS = diode;										//Set ADC input
		ADC0.COMMAND = ADC_STCONV_bm;								//Start conversion
		loop_until_bit_is_clear(ADC0.COMMAND,ADC_STCONV_bp);		//Wait until conversion finished
		return ADC0.RES;
	}
	