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
long is_shot_hit_monster(const std::vector<MonsterRenderInfo>& monsters_render_info);

class Game {
public:
    Screen screen;
    Player player;
    World world;
    std::vector<Weapon> weapons;
    Logger* logger;
    bool isRunning = true;

    Game(const Screen& initialScreen, const Player& initialPlayer, World initialWorld);
    Game(int screen_width,
         int screen_height,
         float player_x,
         float player_y,
         float player_angle_x,
         float player_angle_y,
         float player_fov,
         float player_moving_speed,
         float player_rotate_speed,
         int player_health,
         Logger* logger,
         std::vector<Weapon> weapons);

    void run_game();
    void close_game();
    bool is_game_over() const;

private:
    std::vector<RayOutput> last_rays_output;

    void event_listener();
    void event_handler(SDL_Event event);
    void handle_movement_key_events();
    void handle_mouse_motion_event(SDL_Event event);
    void handle_weapon_shoot_event();
    long is_shot_hit_monster(const std::vector<MonsterRenderInfo>& monsters_render_info) const;
};


#endif //RAYCASTING_GAME_H
