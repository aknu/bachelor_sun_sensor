# bachelor_sun_sensor

The program takes 4 inputs from a quad-photodiode and calculates x- and y-values. These values are converted to two angles, phi ranging from 0 - 30 degrees and theta ranging from 0 - 360 degrees. These angles are then sent to a master device over i2c.

v0.5 changes
  - New code for transmitting data with I2C that sends data untill master sends NACK
    - Added several functions for preparing data to be transmitted
    - Added variables to keep track of number of bytes transmitted and first byte transmitted

v0.4 changes 
  - Added folder structure (.c files in src folder and .h files in include folder), and added studio project
  - Cleaned up main.c
    - Moved ISR into i2c_slave.c, moved getAngles function into sun_sensor.c
    - Moved variable declarations into apporpriate header files
  -  Added function to calculate vector R[xv,yv,zv] from angles 
  -  Corrected some errors with calculating angles
  -  Changed diode definitions to typedef enum
  -  Changed ISR so the slave sends ACK right after receiving cmd from master
  -  Added several to-do's in the code
