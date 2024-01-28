
#include <stdbool.h>
#include "physics.h"

float start_speed_X (float birdx,float birdy,float birdwidth,float height,float slingx,float slingy, bool birdselect, float V)
{
        if ((sqrt(pow(birdx - slingx + 50, 2) + pow(birdy - slingy, 2)) <= 100) && (birdselect == true))
        {
             V = ((slingx - birdx- 80 + birdwidth /2 )*1.5);
            
        }
         return V;
}
float start_speed_Y (float birdx,float birdy,float birdwidth,float birdheight,float slingx,float slingy, bool birdselect, float V)
{
        if ((sqrt(pow(birdx - slingx + 50, 2) + pow(birdy - slingy, 2)) <= 100) && (birdselect == true))
        {
             V = ((slingy - 34) - birdy + 15 + birdheight / 2);
        }
        return V;
}