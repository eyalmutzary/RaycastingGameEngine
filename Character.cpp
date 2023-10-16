#include "Character.h"

Character::Character(float x, float y, float moving_speed) : x(x), y(y), moving_speed(moving_speed) {}


void Character::move(float moving_angle, float moving_speed, const world_map_t& world_map){
    float actual_speed = moving_speed / FPS;
    float new_x = this->x + actual_speed * std::cos(moving_angle);
    float new_y = this->y + actual_speed * std::sin(moving_angle);
    if (world_map[int(new_y)][int(new_x)] != 0) { // handle touching walls
        if (world_map[int(new_y)][int(this->x)] == 0) { // in case of touching, slow down the player
            new_x = this->x;
            new_y = this->y + actual_speed * std::sin(moving_angle) * 0.3;
        } else if (world_map[int(this->y)][int(new_x)] == 0) {
            new_x = this->x + actual_speed * std::cos(moving_angle) * 0.3;
            new_y = this->y;
        } else {
            new_x = this->x;
            new_y = this->y;
        }
    }
    this->x = new_x;
    this->y = new_y;
}
