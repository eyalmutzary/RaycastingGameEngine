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
    this->wall_types = {
            {85, 85, 85, 255},   // A muted gray
            {68, 68, 68, 255},   // A darker shade of gray
            {51, 51, 51, 255},   // A slightly lighter gray
            {102, 34, 34, 255},  // Dark red with a hint of brown
            {85, 34, 85, 255},   // Deep purple with muted tones
            {34, 68, 85, 255}    // Dark blue with a sense of foreboding
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
    float related_height = (SCREEN_HEIGHT/6) / float(height);
    float factor = 1 / std::pow(M_E, related_height);
    if (factor > 1){
        factor = 1;
    }
    color.r *= factor;
    color.g *= factor;
    color.b *= factor;
}


void make_darker_by_distance(Color& color, float distance) {
    float factor = 1 / std::pow(M_E, distance/6);
    if (factor > 1){
        factor = 1;
    }
    color.r *= factor;
    color.g *= factor;
    color.b *= factor;
}

void Screen::render_frame(const std::vector<LineType>& wall_line_lengths, const std::vector<MonsterRenderInfo>& monsters_render_info) {
    this->clear();
    SDL_ShowCursor(SDL_DISABLE);
    render_sky();
    render_floor();
    render_walls(wall_line_lengths);
    render_monsters(monsters_render_info);
    SDL_RenderPresent(this->renderer);
}

void Screen::drawRect(int x, int y, int w, int h) const{
    SDL_Rect rect(x, y, w, h);
    SDL_RenderFillRect(this->renderer, &rect);
    SDL_RenderDrawRect(this->renderer, &rect);
}

void Screen::render_sky() const{
    Color sky_color = {49, 26, 99};
    // create a gradient background
    for (int i=0; i < SCREEN_HEIGHT/2; i++){
        Color color = sky_color;
        make_darker_by_height(color, SCREEN_HEIGHT/2 - i);
        SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
        drawRect(0, i, SCREEN_WIDTH, 1);
    }
}

void Screen::render_floor() const{
    Color floor_color = {66, 55, 48};
    // create a gradient background
    for (int i=0; i < SCREEN_HEIGHT/2; i++){
        Color color = floor_color;
        make_darker_by_height(color, i);
        SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
        drawRect(0, SCREEN_HEIGHT/2 + i, SCREEN_WIDTH, 1);
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
        SDL_RenderDrawLine(this->renderer, i, std::max(line_start, 0), i, std::min(line_end, SCREEN_HEIGHT));
    }
}

void Screen::render_monsters(const std::vector<MonsterRenderInfo>& monsters_render_info) const{
    // sort monsters by distance
    std::vector<MonsterRenderInfo> monsters_render_info_sorted = monsters_render_info;
    std::sort(monsters_render_info_sorted.begin(), monsters_render_info_sorted.end(), [](const MonsterRenderInfo& a, const MonsterRenderInfo& b){
        return a.distance > b.distance;
    });
    for (const MonsterRenderInfo& monster_render_info : monsters_render_info_sorted){
        float rect_size = float(monster_render_info.width) / float(monster_render_info.texture.size());
        for (int i=0; i < monster_render_info.texture.size(); i++){
            for (int j=0; j < monster_render_info.texture.size(); j++){
                Color p_color = monster_render_info.texture[i][j];
                if (p_color.a == 0){
                    continue;
                }
                make_darker_by_distance(p_color, monster_render_info.distance);
                SDL_SetRenderDrawColor(this->renderer, p_color.r, p_color.g, p_color.b, 255);
                drawRect(std::floor(monster_render_info.x - (monster_render_info.width/2) + i * rect_size), std::floor(SCREEN_HEIGHT/2 + j*rect_size), std::ceil(rect_size), std::ceil(rect_size));
            }
        }
    }

}

void Screen::render_game_over() const{
    SDL_SetRenderDrawColor(this->renderer, 150, 0, 0, 255);
    SDL_RenderClear(this->renderer);
    SDL_RenderPresent(this->renderer);
}
