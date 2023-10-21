#include "Game.h"

#include <utility>

Game::Game(const Screen& initialScreen, const Player& initialPlayer,World  initialWorld)
        : screen(initialScreen), world(std::move(initialWorld)), player(initialPlayer) {

}

Game::Game(int screen_width,
     int screen_height,
     float player_x,
     float player_y,
     float player_angle_x,
     float player_angle_y,
     float player_fov,
     float player_moving_speed,
     float player_rotating_speed,
     int health,
     Logger* logger,
     std::vector<Weapon> weapons)
     :
     screen(screen_width, screen_height),
     world( logger),
     player(player_x, player_y, player_angle_x, player_angle_y, player_fov, player_moving_speed, player_rotating_speed, weapons[0], health),
     weapons(weapons),
     logger(logger)
     { }


void Game::run_game() {
    while (isRunning){
        event_listener();
        if (is_game_over()){
            screen.render_game_over();
            continue;
        }
        world.move_monsters();
        world.process_monsters_animation();
        player.next_frame_state();
        last_rays_output = calc_distance_to_walls(player, world);
        std::vector<LineType> wall_line_lengths = convert_wall_distance_to_height(last_rays_output);
        screen.render_frame(wall_line_lengths,
                            calc_monster_render_info(player, world.monsters, last_rays_output),
                            player);
        SDL_RenderPresent(screen.renderer);
        SDL_Delay(1000 / FPS);
    }

    SDL_DestroyRenderer(screen.renderer);
    SDL_DestroyWindow(screen.window);
    SDL_Quit();
}

void Game::close_game() {
    isRunning = false;
}


void Game::event_listener(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        event_handler(event);
    }
    handle_movement_key_events();
}


void Game::event_handler(SDL_Event event) {
    switch (event.type) {
        case SDL_QUIT:
            close_game();
            break;
        case SDL_MOUSEMOTION:
            handle_mouse_motion_event(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            handle_weapon_shoot_event();
            player.shoot();
            break;
        default:
            break;
    }
}

void Game::handle_movement_key_events(){
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    std::vector<char> pressed_keys = getAllPressedKeys(SDL_GetKeyboardState(NULL));

    float left_angle = M_PI * 0.5;
    float forward_angle = M_PI;
    float right_angle = M_PI * 1.5;
    float backward_angle = 0;
    float final_angle = player.angle_x;
    if (pressed_keys.size() == 2){
        if (pressed_keys[0] == 'W' && pressed_keys[1] == 'A'){
            final_angle += (forward_angle+left_angle) / 2.0f;
        } else if (pressed_keys[0] == 'W' && pressed_keys[1] == 'D') {
            final_angle += (forward_angle+right_angle) / 2.0f;
        } else if (pressed_keys[0] == 'S' && pressed_keys[1] == 'A') {
            final_angle += (backward_angle+left_angle) / 2.0f;
        } else if (pressed_keys[0] == 'S' && pressed_keys[1] == 'D') {
            final_angle += (backward_angle+right_angle+(2*M_PI)) / 2.0f;
        }
    } else {
        if(keystates[SDL_SCANCODE_S]) {}
        if (keystates[SDL_SCANCODE_D]){
            final_angle += M_PI * 1.5, player.moving_speed;
        }
        if (keystates[SDL_SCANCODE_W]){
            final_angle += M_PI, player.moving_speed;
        }
        if (keystates[SDL_SCANCODE_A]){
            final_angle += M_PI * 0.5, player.moving_speed;
        }
    }
    if (final_angle != player.angle_x || keystates[SDL_SCANCODE_S]){
        player.move(final_angle, player.moving_speed, world.world_map);
    }
    if (keystates[SDL_SCANCODE_ESCAPE]){
        close_game();
    }
}

std::vector<char> getAllPressedKeys(const Uint8* keystates) {
    std::vector<char> pressed_keys;
    if (keystates[SDL_SCANCODE_S]) {
        pressed_keys.push_back('S');
    } else if (keystates[SDL_SCANCODE_W]) {
        pressed_keys.push_back('W');
    }
    if (keystates[SDL_SCANCODE_A]) {
        pressed_keys.push_back('A');
    } else if (keystates[SDL_SCANCODE_D]) {
        pressed_keys.push_back('D');
    }
    return pressed_keys;
}

void Game::handle_mouse_motion_event(SDL_Event event) {
    int mouseXRel, mouseYRel;
    SDL_GetRelativeMouseState(&mouseXRel, &mouseYRel);
    player.rotate(mouseXRel, mouseYRel);
    SDL_WarpMouseInWindow(screen.window, screen.width / 2, screen.height / 2);
}

void Game::handle_weapon_shoot_event() {
    if (!player.shoot()) { return; };
    std::vector<MonsterRenderInfo> monsters_render_info_sorted = calc_monster_render_info(player, world.monsters, last_rays_output);
    long monster_id = is_shot_hit_monster(monsters_render_info_sorted);
    if (monster_id != -1) {
        // find that monster with the id, reduce its health by 1. if it is 0 - remove it from the vector
        for (Monster& monster : world.monsters) {
            if (monster.id == monster_id) {
                monster.health -= 1;
                monster.hit_animation.sparks_left = 8;
                if (monster.health == 0) {
                    world.monsters.erase(std::remove_if(world.monsters.begin(), world.monsters.end(), [monster_id](const Monster& monster) {
                        return monster.id == monster_id;
                    }), world.monsters.end());
                }
            }
        }

    }

}

Logger logging ("C:\\MyFolder\\University\\Raycasting\\game.log");

long Game::is_shot_hit_monster(const std::vector<MonsterRenderInfo>& monsters_render_info) const  {
    std::vector<MonsterRenderInfo> monsters_render_info_sorted = monsters_render_info;
    std::sort(monsters_render_info_sorted.begin(), monsters_render_info_sorted.end(), [](const MonsterRenderInfo& a, const MonsterRenderInfo& b) {
        return a.distance < b.distance;
    });
    for (const MonsterRenderInfo& monster_render_info : monsters_render_info_sorted){
        int left_border = monster_render_info.x - monster_render_info.width / 2;
        int right_border = monster_render_info.x + monster_render_info.width / 2;
        logging.log("vertical change: " + std::to_string(screen.vertical_change));
        int upper_border = 0;
        int lower_border = -monster_render_info.height;
        if (left_border < SCREEN_WIDTH / 2 && right_border > SCREEN_WIDTH / 2 && screen.vertical_change <= upper_border && screen.vertical_change >= lower_border){
            return monster_render_info.id;
        };
    }
    return -1;
}

std::vector<RayOutput> calc_distance_to_walls(const Player& player, const World& world){
    std::vector<RayOutput> distances;
    for (int i = 0; i < SCREEN_WIDTH; ++i) {
        float relative_angle = player.fov / 2.0 - player.fov * i / SCREEN_WIDTH;
        float angle = player.angle_x - player.fov / 2.0 + player.fov * i / SCREEN_WIDTH;
        if (angle < 0){
            angle += 2 * M_PI;
        } else if (angle > 2 * M_PI){
            angle -= 2 * M_PI;
        }
        RayOutput ray_output = world.get_distance_from_wall(player.x, player.y, angle);
        float corrected_distance = ray_output.distance * std::cos(relative_angle); // fix fisheye effect
        distances.push_back({corrected_distance, ray_output.wall_type});
    }
    return distances;
}

std::vector<LineType> convert_wall_distance_to_height(const std::vector<RayOutput>& rays_output){
    std::vector<LineType> screen_heights;
    for (int i = 0; i < SCREEN_WIDTH; ++i) {
        screen_heights.push_back({int(SCREEN_HEIGHT / rays_output[i].distance), rays_output[i].wall_type});
    }
    return screen_heights;
}


std::vector<MonsterRenderInfo> calc_monster_render_info(const Player& player, std::vector<Monster>& monsters, const std::vector<RayOutput>& rays_output){
    if (monsters.empty()){
        return {};
    }
    std::vector<MonsterRenderInfo> monsters_render_info;
    bool isVisible;
    int monster_screen_x;
    for (auto& monster : monsters){
        monster.calc_monster_relative_position(player.x, player.y);
        monster_screen_x = monster.calc_monster_screen_x(player.angle_x);
        isVisible = monster.is_monster_visible(player, rays_output, monster_screen_x);
        if (!isVisible){ continue; }
        monsters_render_info.push_back({monster.id, monster_screen_x, monster.calc_monster_width(), monster.calc_monster_height(), monster.distance_from_player, monster.hit_animation.is_sparking, monster.texture});
    }
    return monsters_render_info;
}

bool Game::is_game_over() const{
    for (auto& monster : world.monsters){
        if (monster.distance_from_player < 0.5){
            return true;
        }
    }
    return false;
}
