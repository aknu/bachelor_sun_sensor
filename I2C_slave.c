/*
 * I2C_slave.c
 *
 * Created: 18.03.2021 13:10:45
 *  Author: Andreas Knutli
 */ 

#include "I2C_slave.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void I2C_init(uint8_t slaveAddress)
	{
		sei();
		TWI0.SCTRLA = TWI_DIEN_bm | TWI_APIEN_bm | TWI_ENABLE_bm;
		TWI0.SADDR = slaveAddress << 1;
	}
	
void I2C_sendData(uint8_t cmd, uint16_t theta_i2c, uint16_t phi_i2c)
	{
		switch(cmd)
		{
			case 0x00:
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