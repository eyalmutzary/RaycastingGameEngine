#ifndef RAYCASTING_GLOBALS_H
#define RAYCASTING_GLOBALS_H

#include <vector>

struct Color {
    int r;
    int g;
    int b;
    int a;
};

struct RayOutput{
    float distance;
    int wall_type;
};

extern int FPS;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int MAP_WIDTH;
extern int MAP_HEIGHT;
extern float PLAYER_MOVING_SPEED;
extern float MONSTER_MOVING_SPEED;

typedef std::vector<std::vector<int>> world_map_t;
typedef std::vector<std::vector<Color>> texture_t;

#endif //RAYCASTING_GLOBALS_H
