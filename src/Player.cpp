//
// Created by eyalmu on 26/09/2023.
//

#include "Player.h"
#include <cmath>

Player::Player(
        float x, float y, float angle_x, float angle_y, float fov, float moving_speed, float rotate_speed, Weapon& current_weapon, int health)
        : Character(x, y, moving_speed, health), angle_x(angle_x), angle_y(angle_y), fov(fov), rotate_speed(rotate_speed), current_weapon(current_weapon) {}


void Player::rotate(int direction_x, int direction_y){
    float actual_turn_speed = rotate_speed / FPS;
    this->angle_x = this->angle_x + direction_x * actual_turn_speed;
    if (this->angle_x > 2 * M_PI){
        this->angle_x -= 2 * M_PI;
    }
    if (this->angle_x < 0){
        this->angle_x += 2 * M_PI;
    }

    this->angle_y = this->angle_y + direction_y * actual_turn_speed;
    if (this->angle_y > M_PI){
        this->angle_y = M_PI;
    }
    if (this->angle_y < 0){
        this->angle_y = 0;
    }
}

bool Player::shoot() {
    if (current_weapon.weapon_state == Weapon_state::READY && current_weapon.ammo > 0){
        current_weapon.texture_state.texture_index = 1;
        current_weapon.weapon_state = Weapon_state::FIRING;
        current_weapon.ammo--;
        return true;
    }
    return false;

}

void Player::next_frame_state(){
    bool is_shooting_animation = current_weapon.texture_state.texture_index != 0;
    int length_of_animation_frame = 3;
    bool should_change_frame = is_shooting_animation && current_weapon.texture_state.frames_in_state++ > length_of_animation_frame;
    if (should_change_frame){
        bool is_finished_animation = current_weapon.texture_state.textures.size() == current_weapon.texture_state.texture_index + 1;
        if (is_finished_animation){
            current_weapon.texture_state.texture_index = 0;
            current_weapon.weapon_state = Weapon_state::READY;
        } else {
            current_weapon.texture_state.texture_index++;
        }
        current_weapon.texture_state.frames_in_state = 0;
    }
}