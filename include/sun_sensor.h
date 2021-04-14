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

uint16_t angles[2]; //angles[phi, theta]

float R_vect[3]; //R_vect[x_vect,y_vect,z_vect]

void getVector(float r, float h);

#endif /* SUN_SENSOR_H_ */