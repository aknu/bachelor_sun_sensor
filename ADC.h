/*
 * ADC.h
 *
 * Created: 18.03.2021 13:08:47
 *  Author: Andreas Knutli
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define diodeA ADC_MUXPOS_AIN0_gc  // Not that important, but it is normal practice that defines are all capital letters
#define diodeB ADC_MUXPOS_AIN1_gc
#define diodeC ADC_MUXPOS_AIN2_gc
#define diodeD ADC_MUXPOS_AIN3_gc

void ADC_init(void);

uint16_t ADC_read(uint8_t diode); 

/* Minor code quality improvement, but it would be nice if you created som kind of enum typdef for the input. 
This has two main advantages. 
1) It increases the readability by explicitly stating that the function does not take in any uint8_t, but only some diode type
2) The compiler will complain if you give an invalid input to the function. 
Example:
typedef enum {
    DIODE_A = ADC_MUXPOS_AIN0_gc,
    DIODE_B = ADC_MUXPOS_AIN1_gc,
    DIODE_C = ADC_MUXPOS_AIN2_gc, 
    DIODE_B = ADC_MUXPOS_AIN3_gc,    
} diode_t;
uint16_t ADC_read(diode_t diode)
    */

#endif /* ADC_H_ */