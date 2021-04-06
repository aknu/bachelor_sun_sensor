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
		VREF.ADC0REF = VREF_REFSEL_4V096_gc;	//Set VREF // The requirements say that the system should run at 3V3 volts, so the reference voltage has to be 3V3 or les.  
		ADC0.CTRLC = ADC_PRESC_DIV20_gc;		//Select pre-scaler to 20 (CLK_ADC = 4Mhz/20 = 200kHz)
		ADC0.CTRLA = ADC_ENABLE_bm;				//Enable ADC

		/* Have you thought anything about accumulating more samples for noise supresion? I am suspecting that 
		There will be some amount of noise in the system and some averagin is needed. */
		/*Have you thought anything about increasing the sampling length? The output from an op amp is quit low impedance
		so it might be fine, but I would maybe keep it in the back of my head when you get the board. */
		/* Have you considered making interrupt based ADC measurements, this way the device might go to sleep between measurements to save power */
	}
	
uint16_t ADC_read(uint8_t diode)
	{
		ADC0.MUXPOS = diode;										//Set ADC input
		ADC0.COMMAND = ADC_STCONV_bm;								//Start conversion
		loop_until_bit_is_clear(ADC0.COMMAND,ADC_STCONV_bp);		//Wait until conversion finished
		/*Where is the function loop_until_bit_is_clear comming from? I don't think this will compile. */
		return ADC0.RES;
	}
	