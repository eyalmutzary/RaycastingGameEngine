#ifndef RAYCASTING_WORLD_H
#define RAYCASTING_WORLD_H

#include <vector>
#include <cmath>
#include "globals.h"
#include "Logger.h"
#include "Monster.h"
#include "Textures.h"


class World {
public:
    int height;
    int width;
    std::vector<Monster> monsters; // TODO: change to unordered_map
    std::vector<std::vector<int>> world_map;
    Logger* logger;

    World(Logger* logger);

    RayOutput get_distance_from_wall(float pos_x, float pos_y, float angle) const;
    RayOutput check_horizontal_distance(float pos_x, float pos_y, float angle) const;
    RayOutput check_vertical_distance(float pos_x, float pos_y, float angle) const;
    void move_monsters();
    void process_monsters_animation();

    };

#endif //RAYCASTING_WORLD_H
