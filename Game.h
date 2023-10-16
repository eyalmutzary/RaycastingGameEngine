//
// Created by eyalmu on 26/09/2023.
//

#ifndef RAYCASTING_GAME_H
#define RAYCASTING_GAME_H

#include "Screen.h"
#include "Player.h"
#include "World.h"
#include "Logger.h"
#include "unordered_set"

void event_listener();
void event_handler(SDL_Event event);
std::vector<RayOutput> calc_distance_to_walls(const Player& player, const World& world);
std::vector<LineType> convert_wall_distance_to_height(const std::vector<RayOutput>& distances);
std::vector<char> getAllPressedKeys(const Uint8* keystates);
std::vector<MonsterRenderInfo> calc_monster_render_info(const Player& player, std::vector<Monster>& monsters, const std::vector<RayOutput>& rays_output);


class Game {
public:
    Screen screen;
    Player player;
    World world;
    Logger* logger;
    bool isRunning = true;

    Game(const Screen& initialScreen, const Player& initialPlayer, World initialWorld);
    Game(int screen_width,
         int screen_height,
         float player_x,
         float player_y,
         float player_angle,
         float player_fov,
         float player_moving_speed,
         float player_rotate_speed,
         Logger* logger);

    void run_game();
    void close_game();
    bool is_game_over() const;

private:
    void event_listener();
    void event_handler(SDL_Event event);
    void handle_movement_key_events();
    void handle_mouse_motion_event(SDL_Event event);
    };


#endif //RAYCASTING_GAME_H
