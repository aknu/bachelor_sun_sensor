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
		sei(); // Not that important, but I generally would recommend to enable global interrupts after you are done with all peripheral initialization   
		TWI0.SCTRLA = TWI_DIEN_bm | TWI_APIEN_bm | TWI_ENABLE_bm;
		TWI0.SADDR = slaveAddress << 1;
	}
	
void I2C_sendData(uint8_t cmd, uint16_t theta_i2c, uint16_t phi_i2c)
	{
		switch(cmd)
		{
			case 0x00: // As a general rule I do not like magic numbers, at a minimum they shoud be given a meaningfull name true a define. 
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
	/* You can send more than one byt afther each other on I2C bus, the protocol you have written is very
	ineficent requiring four reads and writes for a complet data transfer. 
	I would recommend trying to rewrite your I2C protocol in such a way that you only need one comand to get 
	all the data. 
	Another problem with you current protocol is that it is not very flexible, every time you add some more data 
	you will need a new switch case. You also have dependencies between the swich case in this function and in the ISR
	This is bound to create issues.
	A simple solution could be to have two functions and three global variables:
	uint8_t i2c_buff[MAX_SIZE_OF_DATA];
	uint8_t i2c_data_size;
	uint8_t i2c_buff_ptr; 
	I2C_setUpData(uint8_t * data, uint8_t size)
	{
		i2c_buff = data;
		i2c_data_size = size;
		i2c_buff_ptr = 0; 
	} 
	I2C_send_data()
	{
		TWI0.SDATA = i2c_buff[i2c_buff_ptr];
		i2c_buff_ptr = (i2c_buff_ptr + 1)%i2c_data_size
	}
	The when ever you get a new comand about writing something you call I2C_setUpData() to set up the correct data 
	transfere and when you get a I2C read you call I2C_send_data(). 
	This is just an easy example, I have not tested that it works. It is more just a suggestion to lustrate what I mean. */
	
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