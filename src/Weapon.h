//
// Created by eyalmu on 20/10/2023.
//

#ifndef RAYCASTING_WEAPON_H
#define RAYCASTING_WEAPON_H

#include "globals.h"

// enum for weapon state
enum Weapon_state {
    READY,
    FIRING,
    RELOADING
};

struct Texture_state {
    std::vector<texture_t> textures;
    int texture_index;
    int frames_in_state;
};

class Weapon {
public:
    Texture_state texture_state;
    Weapon_state weapon_state;
    int ammo;
    int damage;
    int fire_rate;
    int reload_time;
    float bullet_speed;

    Weapon(
            Texture_state& texture_state,
            Weapon_state weapon_state,
            int ammo,
            int damage,
            int fire_rate,
            int reload_time,
            float bullet_speed);



};


#endif //RAYCASTING_WEAPON_H
