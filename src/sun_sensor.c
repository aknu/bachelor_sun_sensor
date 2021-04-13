/*
 * sun_sensor.c
 *
 * Created: 13.04.2021 14:45:54
 *  Author: Andreas Knutli
 */ 

#include "../include/sun_sensor.h"
#include <avr/io.h>
#include <math.h>


void getVector(float r, float h){
	
	A = 9;//ADC_read(diodeA);
	B = 3;//ADC_read(diodeB);
	C = 1;//ADC_read(diodeC);
	D = 3; //ADC_read(diodeD);
	
	x = (float)(B+C-A-D)/(A+B+C+D)*r;
	y = (float)(A+B-C-D)/(A+B+C+D)*r;
	
	/*
	Converting x and y to spherical coordinate angles
	phi and theta, and correcting theta to range from 0 to 360
	depending on the current quadrant
	*/
	
	phi = atan(sqrt(pow(x,2)+pow(y,2))/h);

	if(x < 0)		      //-x,+y and -x,-y
	{
		theta = atan(y/x)+M_PI;
	}
	else
	{
		if(y < 0)				//+x,-y
		{
			theta = atan(y/x)+M_2_PI;
		}
		
		else if(y > 0)	//+x,+y
		{
			theta = atan(y/x);
		}
		else						//x=y=0
		{
			theta = 0;
		}
	}
	/*
	Converting phi and theta to degrees and loading into array
	as 16-bit values
	*/
	angles[0] = (uint16_t)round((phi*180/M_PI*100));
	angles[1] = (uint16_t)round((theta*180/M_PI*100));
	/*
	Converting spherical coordinates into a vector R[xv,yv,zv]
	*/
	R_vect[0] = sin(phi)*cos(theta);  //xv
	R_vect[1] = sin(phi)*sin(theta);  //yv
	R_vect[2] = cos(phi);             //zv
}