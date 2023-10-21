#include "Screen.h"
#include "World.h"

#define LOGS_PATH "C:\\MyFolder\\University\\Raycasting\\game.log"

using std::string;

SDLObjects init_screen(int width, int height) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return {};
    }

    SDL_Window* window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return {};
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return {};
    }
    return {window, renderer};
}

Screen::Screen(int width, int height) : width(width), height(height) {
    SDLObjects sdlObjects = init_screen(width, height);
    auto [window, renderer] = sdlObjects;
    if (renderer == nullptr || window == nullptr) {
        return;
    }
    this->window = window;
    this->renderer = renderer;
    // genereate random 8 little dark and spooky colors
    this->wall_types = {
            {
                    {128, 128, 128, 255}, // Normal Gray
                    {100, 80, 90, 255}, // Soft Purple
                    {160, 0, 70, 255}, // Bright Blood Red
                    {0, 100, 100, 255}, // Eerie Teal
                    {150, 0, 150, 255}, // Lavender
                    {100, 0, 100, 255}, // Muted Violet
                    {120, 60, 0, 255}, // Burnt Orange
                    {168, 140, 3, 255},
                    {232, 28, 52, 255}// Crazy Yellow
            }
    };


}


Screen::~Screen() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Screen::clear() {
    SDL_SetRenderDrawColor(this->renderer, 0,0,0, 255);
    SDL_RenderClear(this->renderer);
}

void make_darker_by_height(Color& color, int height){
    float related_height = (SCREEN_HEIGHT/FOG_FACTOR) / float(height);
    float factor = 1 / std::pow(M_E, related_height);
    if (factor > 1){
        factor = 1;
    }
    color.r *= factor;
    color.g *= factor;
    color.b *= factor;
}


void make_darker_by_distance(Color& color, float distance) {
    float factor = 1 / std::pow(M_E, distance/FOG_FACTOR);
    if (factor > 1){
        factor = 1;
    }
    color.r *= factor;
    color.g *= factor;
    color.b *= factor;
}

void make_sparking_effect(Color& color) {
    color.r = std::min(color.r + 120, 255);
}

int calc_vertical_change(float player_angle_y) {
    return SCREEN_HEIGHT - int(double(player_angle_y /  (M_PI/2)) * SCREEN_HEIGHT);
}

void Screen::render_frame(const std::vector<LineType>& wall_line_lengths, const std::vector<MonsterRenderInfo>& monsters_render_info, const Player& player) {
    this->clear();
    SDL_ShowCursor(SDL_DISABLE);
    vertical_change = calc_vertical_change(player.angle_y);
    render_sky();
    render_floor();
    render_walls(wall_line_lengths);
    render_monsters(monsters_render_info);
    render_game_overlay(player);
    SDL_RenderPresent(this->renderer);
}

void Screen::drawRect(int x, int y, int w, int h) const{
    SDL_Rect rect(x, y, w, h);
    SDL_RenderFillRect(this->renderer, &rect);
    SDL_RenderDrawRect(this->renderer, &rect);
}

void Screen::render_sky() const{
    Color sky_color = {70, 40, 120};
    // create a gradient background
    for (int i=0; i < SCREEN_HEIGHT/2 + vertical_change; i++){
        Color color = sky_color;
        make_darker_by_height(color, SCREEN_HEIGHT/2 - i + vertical_change);
        SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
        drawRect(0, i, SCREEN_WIDTH, 1);
    }
}

void Screen::render_floor() const{
    Color floor_color = {77, 65, 56};
    // create a gradient background
    for (int i=0; i < SCREEN_HEIGHT/2 - vertical_change; i++){
        Color color = floor_color;
        make_darker_by_height(color, i);
        SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
        drawRect(0, SCREEN_HEIGHT/2 + i + vertical_change, SCREEN_WIDTH, 1);
    }
}


void Screen::render_walls(const std::vector<LineType>& line_lengths) const {
    for (int i=0; i < SCREEN_WIDTH; i++){
        LineType line_settings = line_lengths[i];
        int line_height = int(line_settings.height);
        int line_start = (SCREEN_HEIGHT - line_height) / 2;
        int line_end = (SCREEN_HEIGHT + line_height) / 2;
        Color color = this->wall_types[line_settings.type];
        make_darker_by_height(color, line_settings.height);
        SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(this->renderer, i, line_start + vertical_change, i, line_end + vertical_change);
    }
}

void Screen::render_image(texture_t texture, int image_width, int image_height, float distance, int x_pos, int y_pos, bool is_sparking) const {
    float rect_size_x = float(image_width) / float(texture[0].size());
    float rect_size_y = float(image_height) / float(texture.size());
    for (int i=0; i < texture.size(); i++){
        for (int j=0; j < texture[0].size(); j++){
            Color p_color = texture[i][j];
            if (p_color.a == 0){
                continue;
            }
            make_darker_by_distance(p_color, distance);
            if (is_sparking){
                make_sparking_effect(p_color);
            }
            SDL_SetRenderDrawColor(this->renderer, p_color.r, p_color.g, p_color.b, 255);
            drawRect(std::floor(x_pos - (image_width/2) + i * rect_size_x),
                     std::floor(y_pos + j*rect_size_y),
                     std::ceil(rect_size_x),
                     std::ceil(rect_size_y));
        }
    }
}

void Screen::render_monsters(const std::vector<MonsterRenderInfo>& monsters_render_info) const{
    // sort monsters by distance
    std::vector<MonsterRenderInfo> monsters_render_info_sorted = monsters_render_info;
    std::sort(monsters_render_info_sorted.begin(), monsters_render_info_sorted.end(), [](const MonsterRenderInfo& a, const MonsterRenderInfo& b){
        return a.distance > b.distance;
    });
    for (const MonsterRenderInfo& monster_render_info : monsters_render_info_sorted){
        render_image(monster_render_info.texture, monster_render_info.width, monster_render_info.width, monster_render_info.distance, monster_render_info.x,  SCREEN_HEIGHT/2 + vertical_change, monster_render_info.is_sparking);
    }
}

void Screen::render_game_overlay(const Player& player) const {
    render_weapon(player.current_weapon);
    render_weapon_aim();
}

void Screen::render_weapon(const Weapon& weapon) const{
    texture_t weapon_texture = weapon.texture_state.textures[weapon.texture_state.texture_index];
    float weapon_scale = 4;
    render_image(weapon_texture, int(weapon_texture[0].size() * weapon_scale), int(weapon_texture.size() * weapon_scale),0, SCREEN_WIDTH*0.68, SCREEN_HEIGHT - int(weapon_texture[0].size() * weapon_scale), false);
}

void Screen::render_weapon_aim() const{
    SDL_SetRenderDrawColor(this->renderer, 209, 155, 67, 255);
    SDL_RenderDrawLine(this->renderer, SCREEN_WIDTH/2 - 12, SCREEN_HEIGHT/2, SCREEN_WIDTH/2 -5, SCREEN_HEIGHT/2);
    SDL_RenderDrawLine(this->renderer, SCREEN_WIDTH/2 + 5, SCREEN_HEIGHT/2, SCREEN_WIDTH/2 + 12, SCREEN_HEIGHT/2);
    SDL_RenderDrawLine(this->renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 12, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 5);
    SDL_RenderDrawLine(this->renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 5, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 12);
}

void Screen::render_game_over() const{
    SDL_SetRenderDrawColor(this->renderer, 150, 0, 0, 255);
    SDL_RenderClear(this->renderer);
    SDL_RenderPresent(this->renderer);
}
