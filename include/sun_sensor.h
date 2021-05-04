/*
 * sun_sensor.h
 *
 * Created: 13.04.2021 16:43:54
 *  Author: andre
 */ 


#ifndef SUN_SENSOR_H_
#define SUN_SENSOR_H_

#include <avr/io.h>

int32_t A;
int32_t B;
int32_t C;
int32_t D;

float h;
float r;

float x;
float y;

float phi;
float theta;

uint8_t angles[4]; //angles[phi, theta]
uint8_t R_vect[6]; //R[xMSB, xLSB, yMSB, yLSB, zMSB, zLSB]
uint8_t ADC_values[8]; //[A_MSB, A_LSB, B_MSB, B_LSB....]

void getAngles(void);

void setUpAngles(void);

void setUpVector(void);

void setUpADCvalues(void);

#endif /* SUN_SENSOR_H_ */