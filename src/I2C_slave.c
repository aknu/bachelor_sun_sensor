/*
 * I2C_slave.c
 *
 * Created: 18.03.2021 13:10:45
 *  Author: Andreas Knutli
 */ 

#include "../include/I2C_slave.h"
#include "../include/sun_sensor.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdbool.h>

/* TO DO:
	- Create function to set new I2C address
	- Move getVector function out from ISR
*/
	
ISR(TWI0_TWIS_vect)
{
	if((TWI0.SSTATUS & TWI_APIF_bm) && (TWI0.SSTATUS & TWI_AP_bm))		//Address interrupt
	{
		I2C_sendAck();													//Send ACK after address received
	}
	else if(TWI0.SSTATUS & TWI_DIF_bm)									//Data interrupt
	{
		if(TWI0.SSTATUS & TWI_DIR_bm)									//Master read from slave
		{
			I2C_sendData();
		}
		else{															//Master write to slave
			cmd = TWI0.SDATA;
			I2C_sendNack();												//Send NACK after data received
			// TODO: Move switch case out from ISR
			switch(cmd)
			{
				case 0x02:
					//Make function to set new I2C address
				case 0x04: //Master requests angles phi and theta
					getAngles();
					setUpAngles();
					I2C_setUpData(angles,4);
					break;
				case 0x05: //Master requests vector R[xMSB, xLSB, yMSB, yLSB, zMSB, zLSB]
					getAngles();
					setUpVector();
					I2C_setUpData(R_vect, 6);
					break;
				case 0x06:
					getAngles();
					setUpADCvalues();
					I2C_setUpData(ADC_values, 8);
					break;
			}
		}
	}
}

void I2C_init(uint8_t slaveAddress)
{
	TWI0.SCTRLA = TWI_DIEN_bm | TWI_APIEN_bm | TWI_ENABLE_bm | TWI_SMEN_bm;	//Enable I2C and data and address interrupts
	TWI0.SADDR = slaveAddress << 1;								//Set slave address
	I2C_isFirstByte = true;										//Set counters for transmitting data
	I2C_byte_counter = 0;
}
	
void I2C_setUpData(uint8_t data[], uint8_t data_size)
{
	I2C_data_size = data_size;				
	for(uint8_t i = 0; i < data_size; i++)	//Set up data to be transmitted
	{
		I2C_data[i] = data[i];
	}
}
	
void I2C_sendData(void)
{
	if(I2C_isFirstByte)						//if first byte of transmission
	{
		I2C_isFirstByte = false;
		TWI0.SDATA = I2C_data[I2C_byte_counter%I2C_data_size];	//Load data for master to read
		I2C_byte_counter++;										//Increment counter
		loop_until_bit_is_set(TWI0_SSTATUS,TWI_DIF_bp);			//Wait until data has been transmitted. This will trigger new interrupt
	}
	else if(!(TWI0.SSTATUS & TWI_RXACK_bm)) //if RXACK == 0 (received ACK)
	{
		TWI0.SDATA = I2C_data[I2C_byte_counter%I2C_data_size];	//Load data for master to read
		I2C_byte_counter++;										//Increment counter
		loop_until_bit_is_set(TWI0_SSTATUS,TWI_DIF_bp);			//Wait until data has been transmitted. This will trigger new interrupt
	}
	else                                    //if RXACK == 1 (received NACK)
	{
		TWI0.SDATA = 0;			//(not sure why this line is needed? programs hangs here without this line...)
		I2C_isFirstByte = 1;	//Reset counters
		I2C_byte_counter = 0;
	}
}
	
void I2C_sendAck(void)
{
	TWI0.SCTRLB = TWI_ACKACT_ACK_gc;
	TWI0.SCTRLB |= TWI_SCMD_RESPONSE_gc;
}
	
void I2C_sendNack(void)
{
	TWI0.SCTRLB = TWI_ACKACT_NACK_gc;
	TWI0.SCTRLB |= TWI_SCMD_RESPONSE_gc;
}