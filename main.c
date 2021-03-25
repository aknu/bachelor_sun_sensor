/*
 * AVRDB_test0.6_interrupts.c
 *
 * Created: 16.03.2021 15:46:52
 * Author : andre
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "ADC.h"
#include "I2C_slave.h"

uint8_t slaveAddress = 0x08;
uint8_t cmd;

int32_t A = 5;
int32_t B = 20;
int32_t C = 100;
int32_t D = 20;

float h = 2.18e-3;
float r = 1.26e-3;

float x;
float y;

float phi;
float theta;

uint16_t phi_i2c;
uint16_t theta_i2c;

ISR(TWI0_TWIS_vect){
	if((TWI0.SSTATUS & TWI_APIF_bm) && (TWI0.SSTATUS & TWI_AP_bm))		//Address interrupt
	{						
		I2C_sendAck();													//Send ACK
	}
	else if(TWI0_SSTATUS & TWI_DIF_bm)									//Data interrupt
	{
		if(TWI0.SSTATUS & TWI_DIR_bm)									//Master read from slave
		{					
			//I2C_sendData(cmd,theta_i2c,phi_i2c);
			
			switch(cmd)
			{
				case 0x00:
					PORTC.OUT = 100;
					TWI0.SDATA = (theta_i2c >> 8) & 0xFF;			//theta MSB
					break;
				case 0x01:
					TWI0.SDATA = (theta_i2c >> 0) & 0xFF;			//theta LSB
					break;
				case 0x02:
					TWI0.SDATA = (phi_i2c >> 8) & 0xFF;				//phi MSB
					break;
				case 0x03:
					TWI0.SDATA = (phi_i2c >> 0) & 0xFF;				//phi LSB
					break;
				default:
					TWI0.SDATA = 111;
			}
		}
		else															//Master write to slave
		{											
			cmd = TWI0.SDATA;
			switch(cmd)
			{
				case 0x04:
					/*
					A = ADC_read(diodeA);
					B = ADC_read(diodeB);
					C = ADC_read(diodeC);
					D = ADC_read(diodeD);
					*/
					x = (float)(B+C-A-D)/(A+B+C+D)*r;
					y = (float)(A+B-C-D)/(A+B+C+D)*r;
					
					phi = atan((float)sqrt(pow(x,2)+pow(y,2))/h)*180/M_PI;

					if(x < 0)											//-x,+y and -x,-y
					{
						PORTC.OUT = 1;
						theta = atan(y/x)*180/M_PI*-1+180;
					}
					else
					{
						if(y < 0)										//+x,-y
						{
							PORTC.OUT = 2;
							theta = atan(y/x)*180/M_PI*-1;
						}
						else if(y > 0)									//+x,+y
						{
							PORTC.OUT = 4;
							theta = atan(y/x)*180/M_PI*-1+360;
						}
						else											//x=y=0
						{
							PORTC.OUT = 8;
							theta = 0;
						}
					}
					break;
				phi_i2c = (int)round((phi*100));
				theta_i2c = (int)round((theta*100));
			}
		}
		I2C_sendAck();													//Send ACK
	}
	else //Stop interrupt
	{
		
	}
}

int main(void)
{
	I2C_init(slaveAddress);
	ADC_init();
	PORTC.DIR = 0xFF;

    while (1)
    {	

    }
}
