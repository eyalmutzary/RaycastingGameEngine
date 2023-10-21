#include <SDL.h>
#include "Logger.h"
#include "Game.h"
#include "globals.h"
#include "Weapon.h"

#define LOGS_PATH "C:\\MyFolder\\University\\Raycasting\\game.log"


void create_weapons(std::vector<Weapon> *weapons) {
    Texture_state shotgun_state = {
            {shotgun_texture_1, shotgun_texture_2, shotgun_texture_3, shotgun_texture_4, shotgun_texture_5}, 0,0
    };
    Weapon shotgun = {
            shotgun_state,
            Weapon_state::READY,
            10, 10, 10, 10, 10.0
    };
    *weapons = {shotgun};
}


int main(int argc, char* args[]) {
    int screen_width = 800;
    int screen_height = 600;
    int world_width = 1000;
    int world_height = 1000;
    float player_x = 400.0f;
    float player_y = 300.0f;
    float player_angle_x = 0.0f;
    float player_angle_y = 0.0f;
    float player_fov = 90.0f;
    float player_moving_speed = 5.0f;
    float player_rotate_speed = 5.0f;
    int player_health = 3;
    std::vector<Weapon> weapons;
    create_weapons(&weapons);
    Logger logger(LOGS_PATH);

    Game game({screen_width=SCREEN_WIDTH,
                screen_height=SCREEN_HEIGHT,
                player_x = 2.5f,
                player_y = 2.5f,
                player_angle_x = M_PI,
                player_angle_y = M_PI / 2,
                player_fov = 2*M_PI / 6.0f,
                player_moving_speed = PLAYER_MOVING_SPEED,
                player_rotate_speed = 0.2f,
                player_health = 3,
                      &logger,
                      weapons
    });

    game.run_game();

    return 0;
}
