/*
 * SunSensor_AVRDB_v0.4.c
 *
 * Created: 13.04.2021 16:47:42
 * Author : Andreas Knutli
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "include/ADC.h"
#include "include/I2C_slave.h"
#include "include/sun_sensor.h"


int main(void)
{	
	slaveAddress = 0x08;
	
	h = 2.18e-3;
	r = 1.26e-3;
	
	I2C_init(slaveAddress);
	ADC_init();
	
	
    while (1)
    {	

    }
}


