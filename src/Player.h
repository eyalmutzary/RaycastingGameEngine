
//
// Created by eyalmu on 26/09/2023.
//

#ifndef RAYCASTING_PLAYER_H
#define RAYCASTING_PLAYER_H

#include "globals.h"
#include "Character.h"
#include "Weapon.h"
#include "Logger.h"

class Player : public Character{
public:
    float angle_x;
    float angle_y;
    float fov;
    float rotate_speed;
    Weapon current_weapon;

    Player(
            float x,
            float y,
            float angle_x,
            float angle_y,
            float fov,
            float moving_speed,
            float rotate_speed,
            Weapon& current_weapon,
            int health);

    void rotate(int direction_x, int direction_y);
    bool shoot();
    void next_frame_state();

};


#endif //RAYCASTING_PLAYER_H
