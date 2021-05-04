/*
 * I2C_slave.h
 *
 * Created: 18.03.2021 14:02:19
 *  Author: andre
 */ 


#ifndef I2C_SLAVE_H_
#define I2C_SLAVE_H_

#include <avr/io.h>
#include <stdbool.h>

uint8_t cmd;
uint8_t slaveAddress;
uint8_t n;


uint8_t I2C_data[6];
uint8_t I2C_data_size;
uint8_t I2C_byte_counter;

bool I2C_isFirstByte;

void I2C_init(uint8_t slaveAddress);

void I2C_setUpData(uint8_t data[], uint8_t data_size);

void I2C_sendData(void);

void I2C_sendAck(void);

void I2C_sendNack(void);

#endif /* I2C_SLAVE_H_ */