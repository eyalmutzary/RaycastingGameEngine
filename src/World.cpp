#include "World.h"

World::World(Logger* logger) : logger(logger) {
//    world_map= {
//            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//            {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//            {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
//    };
    world_map = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2},
            {1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,0,0,2},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,0,0,2},
            {1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,2,0,0,3,3,0,0,3,3,0,0,2},
            {1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,3,3,0,0,2},
            {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,2,0,0,0,0,0,0,0,0,0,0,2},
            {4,4,4,4,4,4,0,1,0,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,0,0,2},
            {4,0,0,0,0,4,0,1,0,0,0,0,0,0,0,0,0,1,0,0,2,0,0,3,3,0,0,3,3,0,0,2},
            {4,0,0,2,0,4,0,1,0,0,0,0,0,0,0,0,0,1,0,0,2,0,0,3,3,0,0,3,3,0,0,2},
            {4,2,2,2,0,4,0,1,1,1,1,1,1,1,0,1,1,1,0,0,2,0,0,0,0,0,0,0,0,0,0,2},
            {4,0,0,0,0,4,0,0,0,0,0,0,0,1,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2},
            {4,0,2,2,2,4,4,4,4,4,4,4,0,1,0,1,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2},
            {4,0,0,0,0,0,0,0,0,0,0,4,4,4,0,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,1},
            {4,0,0,0,0,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,7,7,7,7,7,7},
            {4,0,0,0,0,4,0,0,0,4,4,4,4,4,1,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
            {4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,7,7,7,7,7,7,0,0,0,7},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,7,0,0,0,0,7,0,0,0,7},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,0,0,0,7},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,7,0,0,0,0,0,0,7},
            {1,0,5,6,5,6,5,6,5,6,5,6,5,6,1,0,0,0,0,0,0,0,1,1,7,0,0,0,0,0,0,7},
            {1,0,6,0,0,0,0,0,0,0,0,0,0,6,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,7},
            {1,0,5,0,0,0,0,0,0,0,0,0,0,5,1,0,0,5,0,5,0,0,1,1,7,0,0,0,0,0,0,7},
            {1,0,6,0,0,0,0,0,0,0,0,0,0,6,1,0,0,0,0,0,0,0,1,0,7,0,0,0,0,0,0,7},
            {1,0,5,0,0,0,0,0,0,0,0,0,0,5,1,0,0,0,0,0,0,0,1,0,7,7,7,7,7,7,7,7},
            {1,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,5,0,0,1,0,0,0,0,0,0,0,0,1},
            {1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
            {1,0,6,0,0,0,0,0,0,0,0,0,0,5,1,0,0,0,0,0,0,0,1,0,0,0,8,8,8,8,8,1},
            {1,0,5,0,0,0,0,0,0,0,0,0,0,6,1,0,0,5,0,5,0,0,8,8,8,8,8,0,0,0,8,1},
            {1,0,6,0,0,0,0,0,0,0,0,0,0,5,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,1},
            {1,0,6,5,6,5,6,5,6,5,6,5,6,6,1,0,0,0,0,0,0,0,8,8,8,8,8,0,0,0,8,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,8,8,8,8,8,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };
    monsters = {
            {14, 6, MONSTER_MOVING_SPEED, monster_texture, 2},
            {26, 10, MONSTER_MOVING_SPEED, monster_texture, 2},
            {1.5, 14, MONSTER_MOVING_SPEED, monster_texture, 2},
            {18, 26, MONSTER_MOVING_SPEED, monster_texture, 2},
            {25, 20.5, MONSTER_MOVING_SPEED, monster_texture, 2},
            {5, 22, MONSTER_MOVING_SPEED, monster_texture, 2},
            {5, 26, MONSTER_MOVING_SPEED, monster_texture, 2},

    };

    height = world_map.size();
    width = world_map[0].size();
}

float calc_distance_of_2_points(float x1, float y1, float x2, float y2){
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}


RayOutput World::check_horizontal_distance(float pos_x, float pos_y, float angle) const{
    float ray_x = pos_x;
    float ray_y = pos_y;
    if (!(angle < M_PI)) { // looking up
        while (int(ray_y) > 0 && int(ray_x) > 0 && int(ray_y) < this->world_map.size() && this->world_map[int(ray_y)][int(ray_x)] == 0){
            ray_y = std::ceil(ray_y + 0.01);
            ray_x = pos_x - (pos_y - ray_y) / std::tan(angle);

            if (ray_x < 0 || ray_x > this->width || ray_y < 0 || ray_y > this->height){
                return {100, 1};
            }
        }
    } else { // looking down
        while (int(ray_y) < this->height && int(ray_x) < this->width && this->world_map[int(ray_y)][int(ray_x)] == 0){
            ray_y = std::floor(ray_y - 0.01);
            ray_x = pos_x - (pos_y - ray_y) / std::tan(angle);

            if (ray_x < 0 || ray_x > this->width || ray_y-1 < 0 || ray_y > this->height){
                return {100, 1};
            }
            if (this->world_map[int(ray_y-1)][int(ray_x)] != 0) {break;}
        }
    }
    int wall_type = this->world_map[int(ray_y-1)][int(ray_x)] != 0 ?
            this->world_map[int(ray_y-1)][int(ray_x)] : this->world_map[int(ray_y)][int(ray_x)];
    return {calc_distance_of_2_points(pos_x, pos_y, ray_x, ray_y), wall_type};
}

RayOutput World::check_vertical_distance(float pos_x, float pos_y, float angle) const{
    float ray_x = pos_x;
    float ray_y = pos_y;
    if (!(angle < M_PI / 2 || angle > 3 * M_PI / 2)){ // looking left
        while (int(ray_y) > 0 && int(ray_x) > 0 && this->world_map[int(ray_y)][int(ray_x)] == 0){
            ray_x = std::ceil(ray_x + 0.01);
            ray_y = pos_y - (pos_x - ray_x) * std::tan(angle);

            if (ray_x < 0 || ray_x > this->width || ray_y < 0 || ray_y > this->height){
                return {100, 1};
            }
        }
    } else { // looking right
        while (int(ray_y) > 0 && int(ray_x) < this->world_map[0].size() && this->world_map[int(ray_y)][int(ray_x)] == 0){
            ray_x = std::floor(ray_x - 0.01);
            ray_y = pos_y - (pos_x - ray_x) * std::tan(angle);
            if (ray_x-1 < 0 || ray_x > this->width || ray_y < 0 || ray_y > this->height){
                return {100, 1};
            }
            if (this->world_map[int(ray_y)][int(ray_x-1)] != 0) {break;}
        }
    }
    int wall_type = this->world_map[int(ray_y)][int(ray_x-1)] != 0 ?
                    this->world_map[int(ray_y)][int(ray_x-1)] : this->world_map[int(ray_y)][int(ray_x)];
    return {calc_distance_of_2_points(pos_x, pos_y, ray_x, ray_y), wall_type};
}

RayOutput World::get_distance_from_wall(float pos_x, float pos_y, float angle) const{
    RayOutput x_ray_output = check_horizontal_distance(pos_x, pos_y, angle);
    RayOutput y_ray_output = check_vertical_distance(pos_x, pos_y, angle);
    if (x_ray_output.distance < y_ray_output.distance){
        return x_ray_output;
    } else {
        return y_ray_output;
    }
}

void World::move_monsters() {
    for (auto &monster : monsters) {
        if (!monster.is_active){ continue; }
        monster.move(monster.angle_from_player, monster.moving_speed, world_map);
    }
}

void World::process_monsters_animation() {
    for (auto& monster : monsters){
        monster.animate();
    }
}