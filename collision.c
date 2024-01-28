#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "physics.h"

typedef struct {
    int h;
    int w;
    int x;
    int y;
    int r;
    int m;
    float alpha; // body angle
    bool round;
} Rigid_body;


bool collision(Rigid_body RB1, Rigid_body RB2) 
{
    if ((RB1.round == 0)&&(RB2.round == 0))
    {
        if (RB1.x < RB2.x + RB2.w &&
                RB1.x + RB1.w > RB2.x &&
                RB1.y < RB2.y + RB2.h &&
                RB1.y + RB1.h > RB2.y) {
                // Obdélníky se protínají
                return 1;
            }
            // Obdélníky se neprotínají
            return 0;
    }
    else if((RB1.round == 1)&&(RB2.round == 1))
    {
        double distance = sqrt(pow((RB1.x + RB1.r) - (RB2.x + RB2.r), 2) + pow((RB1.y + RB1.r) - (RB2.y + RB2.r), 2));
        if(distance <= (RB1.r + RB2.r)) return 1;
        else return 0;

    }
    else if ((RB1.round == 1)&&(RB2.round == 0))
    {
        double closestX = fmax(RB2.x, fmin((RB1.x + RB1.r), RB2.x + RB2.w));
        double closestY = fmax(RB2.y, fmin((RB1.y + RB1.r), RB2.y + RB2.h));

        double distance = sqrt(pow((RB1.x + RB1.r) - closestX, 2) + pow((RB1.y + RB1.r) - closestY, 2));

        if(distance <= RB1.r)return 1;
        else return 0;
        
    }
        else if ((RB1.round == 0)&&(RB2.round == 1))
    {
        double closestX = fmax(RB1.x, fmin((RB2.x + RB2.r), RB1.x + RB1.w));
        double closestY = fmax(RB1.y, fmin((RB2.y + RB2.r), RB1.y + RB1.h));

        double distance = sqrt(pow((RB2.x + RB2.r) - closestX, 2) + pow((RB2.y + RB2.r) - closestY, 2));

        if(distance <= RB2.r) return 1;
        else return 0;
        
    }
    else return 0;
    

}
