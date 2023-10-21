#ifndef RAYCASTING_CHARACTER_H
#define RAYCASTING_CHARACTER_H


#include "globals.h"
#include "cmath"

class Character {
public:
    static long id_counter;
    long id;
    float x;
    float y;
    float moving_speed;
    int health;

    Character(float x, float y, float moving_speed, int health);

    void move(float moving_angle, float moving_speed, const world_map_t& world_map);
};


#endif //RAYCASTING_CHARACTER_H
