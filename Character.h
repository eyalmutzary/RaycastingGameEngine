#ifndef RAYCASTING_CHARACTER_H
#define RAYCASTING_CHARACTER_H


#include "globals.h"
#include "cmath"

class Character {
public:
    float x;
    float y;
    float moving_speed;

    Character(float x, float y, float moving_speed);

    void move(float moving_angle, float moving_speed, const world_map_t& world_map);
};


#endif //RAYCASTING_CHARACTER_H
