/*
 * sun_sensor.c
 *
 * Created: 13.04.2021 14:45:54
 *  Author: Andreas Knutli
 */ 

#include "../include/sun_sensor.h"
#include "../include/I2C_slave.h"
#include "../include/ADC.h"
#include <avr/io.h>
#include <math.h>


void getAngles(void){
	
	A = ADC_read(DIODE_A);
	B = ADC_read(DIODE_B);
	C = ADC_read(DIODE_C);
	D = ADC_read(DIODE_D);
	
	x = (float)(B+C-A-D)/(A+B+C+D)*r;
	y = (float)(A+B-C-D)/(A+B+C+D)*r;
	
	/*
	Converting x and y to spherical coordinate angles
	phi and theta, and correcting theta to range from 0 to 360
	depending on the current quadrant
	*/
	
	phi = atan(sqrt(pow(x,2)+pow(y,2))/h);

	if(x < 0)			{theta = atan(y/x)+M_PI;}	//-x,+y and -x,-y
	else{
		if(y < 0)		{theta = atan(y/x)+M_2_PI;}	//+x,-y
		else if(y > 0)	{theta = atan(y/x);}		//+x,+y
		else			{theta = 0;}				//x=y=0
	}
}

void setUpAngles(void){
	/*
	Converting phi and theta to degrees and loading into array
	as 16-bit values like this: angles[phiMSB, phiLSB, thetaMSB, thetaLSB]
	*/
	angles[0] = ((uint16_t)round(phi*180/M_PI*100) >> 8) & 0xFF;
	angles[1] = ((uint16_t)round(phi*180/M_PI*100) >> 0) & 0xFF;
	angles[2] = ((uint16_t)round(theta*180/M_PI*100) >> 8) & 0xFF;
	angles[3] = ((uint16_t)round(theta*180/M_PI*100) >> 0) & 0xFF;
}

void setUpVector(void){
	/*
	Converting spherical coordinates into a vector R[xMSB, xLSB, yMSB, yLSB, zMSB, zLSB]
	*/
	R_vect[0] = ((uint16_t)round(sin(phi)*cos(theta)*4096+2048) >> 8) & 0xFF; //xMSB
	R_vect[1] = ((uint16_t)round(sin(phi)*cos(theta)*4096+2048) >> 0) & 0xFF; //xLSB
	R_vect[2] = ((uint16_t)round(sin(phi)*sin(theta)*4096+2048) >> 8) & 0xFF; //yMSB
	R_vect[3] = ((uint16_t)round(sin(phi)*sin(theta)*4096+2048) >> 8) & 0x00; //yLSB
	R_vect[4] = ((uint16_t)round(cos(phi)*5120-4096) >> 8) & 0xFF;            //zMSB
	R_vect[5] = ((uint16_t)round(cos(phi)*5120-4096) >> 0) & 0xFF;            //zLSB
}

void setUpADCvalues(void){
	ADC_values[0] = (uint16_t)(A >> 8) & 0xFF;
	ADC_values[1] = (uint16_t)(A >> 0) & 0xFF;
	ADC_values[2] = (uint16_t)(B >> 8) & 0xFF;
	ADC_values[3] = (uint16_t)(B >> 0) & 0xFF;
	ADC_values[4] = (uint16_t)(C >> 8) & 0xFF;
	ADC_values[5] = (uint16_t)(C >> 0) & 0xFF;
	ADC_values[6] = (uint16_t)(D >> 8) & 0xFF;
	ADC_values[7] = (uint16_t)(D >> 0) & 0xFF;
}