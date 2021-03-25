/*
 * I2C_slave.h
 *
 * Created: 18.03.2021 14:02:19
 *  Author: andre
 */ 


#ifndef I2C_SLAVE_H_
#define I2C_SLAVE_H_

#include <avr/io.h>

void I2C_init(uint8_t slaveAddress);

void I2C_sendData(uint8_t cmd, uint16_t theta_i2c, uint16_t phi_i2c);

void I2C_sendAck(void);

void I2C_sendNack(void);

#endif /* I2C_SLAVE_H_ */