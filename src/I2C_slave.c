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

/* TO DO:
	- Rewrite I2C_sendData to send more than one byte at once, and be more flexible
	- Create function to set new I2C address
	- Move getVector function out from ISR
*/

ISR(TWI0_TWIS_vect){
	if((TWI0.SSTATUS & TWI_APIF_bm) && (TWI0.SSTATUS & TWI_AP_bm))		//Address interrupt
	{
		I2C_sendAck();													//Send ACK after address received
	}
	else if(TWI0_SSTATUS & TWI_DIF_bm)									//Data interrupt
	{
		if(TWI0.SSTATUS & TWI_DIR_bm)									//Master read from slave
		{
			I2C_sendData(cmd,angles);
			I2C_sendAck();												//Send ACK after data sent
		}
		else															//Master write to slave
		{
			cmd = TWI0.SDATA;
			I2C_sendAck();												//Send ACK after data received
			switch(cmd)
			{
				case 0x04:
				// TO DO: Move this function out of ISR?
				getVector(r,h);
				break;
				case 0x05:
				// TO DO: Function to set I2C address
				break;
			}
		}
	}
}

void I2C_init(uint8_t slaveAddress)
	{
		sei();
		TWI0.SCTRLA = TWI_DIEN_bm | TWI_APIEN_bm | TWI_ENABLE_bm;
		TWI0.SADDR = slaveAddress << 1;
	}
	
void I2C_sendData(uint8_t cmd, uint16_t angles[])
	//TO DO: Write more efficient code for transmitting data
	{
		switch(cmd)
		{
			case 0x00:
				TWI0.SDATA = (angles[1] >> 8) & 0xFF;			//theta MSB
				break;
			case 0x01:
				TWI0.SDATA = (angles[1] >> 0) & 0xFF;			//theta LSB
				break;
			case 0x02:
				TWI0.SDATA = (angles[0] >> 8) & 0xFF;				//phi MSB
				break;
			case 0x03:
				TWI0.SDATA = (angles[0] >> 0) & 0xFF;				//phi LSB
				break;
			default:
				TWI0.SDATA = 111;
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