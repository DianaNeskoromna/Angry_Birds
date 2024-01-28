#ifndef COLLISION_H_
#define COLLISION_H_
#include <stdbool.h>
#include <SDL2/SDL.h>

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

bool collision(Rigid_body RB1, Rigid_body RB2);
#endif