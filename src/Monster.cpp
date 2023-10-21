#include "Monster.h"


Monster::Monster(float x, float y, float moving_speed, texture_t texture, int health)
        : Character(x, y, moving_speed, health), texture(texture){
    hit_animation = {0, false, 0};
    distance_from_player = 99;
    angle_from_player = 0;
    is_active = false;
};


void Monster::calc_monster_relative_position(float player_x, float player_y) {
    distance_from_player = std::sqrt(std::pow(x - player_x, 2) + std::pow(y - player_y, 2));
    if (player_x <= x){ // player is on the left of the monster
        if (player_y <= y) { // player is above the monster
            angle_from_player = 1.5 * M_PI - std::atan2(x - player_x, y - player_y);
        } else {
            angle_from_player = M_PI - std::atan2(player_y - y, x - player_x);
        }
    } else { // player is on the right of the monster
        if (player_y <= y) { // player is above the monster
            angle_from_player = 1.5 * M_PI + std::atan2(player_x - x, y - player_y);
        } else {
            angle_from_player = std::atan2(player_y - y, player_x - x);
        }
    }
}

int Monster::calc_monster_width () const {
    return int(SCREEN_WIDTH / distance_from_player) / 2;
}

int Monster::calc_monster_height () const {
    return int(SCREEN_HEIGHT / distance_from_player) / 2;
}

int Monster::calc_monster_screen_x(const float player_angle){
    if (angle_from_player + M_PI < player_angle){ angle_from_player += 2 * M_PI; }
    if (angle_from_player - M_PI > player_angle){ angle_from_player -= 2 * M_PI; }
    return int((angle_from_player - player_angle) * SCREEN_WIDTH) + SCREEN_WIDTH / 2;
}


bool Monster::is_monster_visible(const Player& player, const std::vector<RayOutput>& rays_output, int monster_screen_x) {
    // check if not behind a wall
    float epsilon = 0.1;
    if (monster_screen_x > SCREEN_WIDTH || monster_screen_x < 0 || distance_from_player > rays_output[monster_screen_x].distance + epsilon){
        return false;
    }
    is_active = true;

    // check if in fov
    if(!is_monster_in_fov(player)){
        return false;
    }

    return true;
}


bool Monster::is_monster_in_fov(const Player& player) const {
    float left_view_border = player.angle_x - player.fov / 2.0;
    float right_view_border = player.angle_x + player.fov / 2.0;

    left_view_border = fmod(left_view_border, 2 * M_PI);
    right_view_border = fmod(right_view_border, 2 * M_PI);
    if (left_view_border < 0){ left_view_border += 2 * M_PI; }

    if (left_view_border < right_view_border) {
        return left_view_border <= angle_from_player && angle_from_player <= right_view_border;
    } else {
        return left_view_border <= angle_from_player || angle_from_player <= right_view_border;
    }
}


void Monster::animate() {
    if (hit_animation.sparks_left > 0){
        hit_animation.frames_in_current_spark++;
        if (hit_animation.frames_in_current_spark > 1){
            hit_animation.frames_in_current_spark = 0;
            hit_animation.sparks_left--;
            if (hit_animation.sparks_left % 2 == 0){
                hit_animation.is_sparking = false;
            } else {
                hit_animation.is_sparking = true;
            }
        }
    }
}