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

int32_t A;
int32_t B;
int32_t C;
int32_t D;

float h = 2.18e-3;
float r = 1.26e-3;

float x;
float y;

float phi;
float theta;

uint16_t phi_i2c;
uint16_t theta_i2c;

uint16_t angles[2]; //angle[phi_i2c,theta_i2c]

void getAngles(float r, float h){
	
	A = 20;//ADC_read(diodeA);
	B = 5;//ADC_read(diodeB);
	C = 20;//ADC_read(diodeC);
	D = 60; //ADC_read(diodeD);
	
	x = (float)(B+C-A-D)/(A+B+C+D)*r;
	y = (float)(A+B-C-D)/(A+B+C+D)*r;
	
	phi = atan(sqrt(pow(x,2)+pow(y,2))/h)*180/M_PI;

	if(x < 0)											//-x,+y and -x,-y
	{
		theta = atan(y/x)*180/M_PI*-1+180;
	}
	else
	{
		if(y < 0)										//+x,-y
		{
			theta = atan(y/x)*180/M_PI*-1;
		}
		else if(y > 0)									//+x,+y
		{
			theta = atan(y/x)*180/M_PI*-1+360;
		}
		else											//x=y=0
		{
			theta = 0;
		}
	}
	angles[0] = (int)round((phi*100));
	angles[1] = (int)round((theta*100));
}

ISR(TWI0_TWIS_vect){
	if((TWI0.SSTATUS & TWI_APIF_bm) && (TWI0.SSTATUS & TWI_AP_bm))		//Address interrupt
	{						
		I2C_sendAck();													//Send ACK after address received
	}
	else if(TWI0_SSTATUS & TWI_DIF_bm)									//Data interrupt
	{
		if(TWI0.SSTATUS & TWI_DIR_bm)									//Master read from slave
		{					
			I2C_sendData(cmd,theta_i2c,phi_i2c);			
		}
		else															//Master write to slave
		{											
			cmd = TWI0.SDATA;
			switch(cmd)
			{
				case 0x04:
					getAngles(r,h);
					phi_i2c = angles[0];
					theta_i2c = angles[1];
					break;
				case 0x05:
					// Function to set I2C address
					break;
			}
		}
		I2C_sendAck();													//Send ACK
	}
}

int main(void)
{
	I2C_init(slaveAddress);
	ADC_init();

    while (1)
    {	

    }
}
