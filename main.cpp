#include <SDL.h>
#include "Logger.h"
#include "Game.h"
#include "globals.h"

#define LOGS_PATH "C:\\MyFolder\\University\\Raycasting\\game.log"



int main(int argc, char* args[]) {
    int screen_width = 800;
    int screen_height = 600;
    int world_width = 1000;
    int world_height = 1000;
    float player_x = 400.0f;
    float player_y = 300.0f;
    float player_angle = 0.0f;
    float player_fov = 90.0f;
    float player_moving_speed = 5.0f;
    float player_rotate_speed = 5.0f;

    Logger logger(LOGS_PATH);

    Game game({screen_width=SCREEN_WIDTH,
                screen_height=SCREEN_HEIGHT,
                player_x = 3.0f,
                player_y = 2.9f,
                player_angle = M_PI,
                player_fov = 2*M_PI / 6.0f,
                player_moving_speed = PLAYER_MOVING_SPEED,
                player_rotate_speed = 0.2f,
                      &logger});

    game.run_game();

    return 0;
}
