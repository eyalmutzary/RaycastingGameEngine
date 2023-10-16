#ifndef RAYCASTING_MONSTER_H
#define RAYCASTING_MONSTER_H


#include "Character.h"
#include "Player.h"
//#include "World.h"
#include "Logger.h"

class Monster : public Character{
public:
    texture_t texture;
    float distance_from_player;
    float angle_from_player;
    bool is_active;

    Monster(float x, float y, float moving_speed, texture_t texture);
    void calc_monster_relative_position(float player_x, float player_y);
    bool is_monster_visible(const Player& player, const std::vector<RayOutput>& rays_output, int monster_screen_x);
    int calc_monster_width () const;
    int calc_monster_screen_x(const float player_angle);

private:
    bool is_monster_in_fov(const Player& player) const;

};


#endif //RAYCASTING_MONSTER_H
