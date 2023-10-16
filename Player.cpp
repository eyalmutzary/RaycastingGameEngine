//
// Created by eyalmu on 26/09/2023.
//

#include "Player.h"
#include <cmath>

Player::Player(
        float x, float y, float angle, float fov, float moving_speed, float rotate_speed)
        : Character(x, y, moving_speed), angle(angle), fov(fov), rotate_speed(rotate_speed) {}


void Player::rotate(int direction){
    float actual_turn_speed = rotate_speed / FPS;
    this->angle = this->angle + direction * actual_turn_speed;
    if (this->angle > 2 * M_PI){
        this->angle -= 2 * M_PI;
    }
    if (this->angle < 0){
        this->angle += 2 * M_PI;
    }
}