#ifndef MY_PROJECT_PHYSICS_H_
#define MY_PROJECT_PHYSICS_H_
#include <stdbool.h>
#include <SDL2/SDL.h>

float start_speed_X (float birdx,float birdy,float birdwidth,float height,float slingx,float slingy, bool birdselect, float V);
float start_speed_Y (float birdx,float birdy,float birdwidth,float birdheight,float slingx,float slingy, bool birdselect, float V);

#endif