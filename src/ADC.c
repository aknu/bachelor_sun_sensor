/*
 * ADC.c
 *
 * Created: 18.03.2021 12:18:35
 *  Author: Andreas Knutli
 */ 

#include "../include/ADC.h"
#include <avr/io.h>

/* TO DO: 
	- Multiple samples and averaging
	- Longer sampling times
	- Interrupt based ADC
*/

void ADC_init(void)
	{
		VREF.ADC0REF |= VREF_REFSEL_2V048_gc;	//Set VREF
		ADC0.CTRLA |= ADC_RESSEL_12BIT_gc;
		//ADC0.CTRLB |= ADC_SAMPNUM_ACC8_gc;
		ADC0.CTRLC |= ADC_PRESC_DIV20_gc;		//Select pre-scaler to 20 (CLK_ADC = 4Mhz/20 = 200kHz)
		
		ADC0.CTRLA |= ADC_ENABLE_bm;				//Enable ADC
	}
	
uint16_t ADC_read(diode_t diode)
	{
		ADC0.MUXPOS = diode;										//Set ADC input
		ADC0.COMMAND = ADC_STCONV_bm;								//Start conversion
		loop_until_bit_is_set(ADC0.INTFLAGS,ADC_RESRDY_bp);		//Wait until conversion finished
		return ADC0.RES;
	}
	
	
