
//
// Created by eyalmu on 26/09/2023.
//

#ifndef RAYCASTING_PLAYER_H
#define RAYCASTING_PLAYER_H

#include "globals.h"
#include "Character.h"

class Player : public Character{
public:
    float angle;
    float fov;
    float rotate_speed;

    Player(
            float x,
            float y,
            float angle,
            float fov,
            float moving_speed,
            float rotate_speed=10.0f);

    void rotate(int direction);

};


#endif //RAYCASTING_PLAYER_H
