# bachelor_sun_sensor

The program takes 4 inputs from a quad-photodiode and calculates x- and y-values. These values are converted to two angles, phi ranging from 0 - 30 degrees and theta ranging from 0 - 360 degrees. These angles are then sent to a master device over i2c.

/* General comments to the repo: 
1) The repo should include a studio project or a make file or something like this so it is actually possible to compile the project. 
2) It would be nice if the files where organized in some kind of folder structure. Makes it a lot easier once the project starts to grow.
3) How can theta range from 0-360 degrees is the sensor not only facing one way and it should be maximum 0 - 180? 
4) The requirements list a 60 degree FOV does that not mean that phi should have a longer range than 0 - 30 degrees? 
5) The desired output from the sun sensor is not actually the angles, but a vector pointing towards the sun. I am wondering if finding the vector might remove som of the complicated trigonometrical math? I think for testing purposes it would be nice to have access to both the angles and the vector. */