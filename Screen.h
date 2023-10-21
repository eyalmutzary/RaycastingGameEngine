#ifndef RAYCASTING_SCREEN_H
#define RAYCASTING_SCREEN_H

#include <SDL.h>
#include <cstdio>
#include <fstream>
#include "globals.h"
#include "vector"
#include "cmath"
#include "World.h"

struct SDLObjects {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

struct LineType {
    int height;
    int type;
};

struct MonsterRenderInfo {
    long id;
    int x;
    int width;
    int height;
    float distance;
    bool is_sparking;
    texture_t texture;
};

class Screen {
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<Color> wall_types;
    int width;
    int height;
    int vertical_change;

    Screen(int width, int height);

    void draw_line(int x1, int y1, int x2, int y2);
    void draw_quad(int x, int y, int width, int height);

    void clear();
    void render_frame(const std::vector<LineType>& line_lengths, const std::vector<MonsterRenderInfo>& monsters_render_info, const Player& player);
    void render_sky() const;
    void render_floor() const;
    void render_walls(const std::vector<LineType>& line_lengths) const;
    void render_image(texture_t texture, int image_width, int image_height, float distance, int x_pos, int y_pos, bool is_sparking) const;
    void render_monsters(const std::vector<MonsterRenderInfo>& monstersImages) const;
    void render_weapon(const Weapon& weapon) const;
    void render_weapon_aim() const;
    void render_game_overlay(const Player& player) const;
    void render_game_over() const;

    ~Screen();

private:
    void drawRect(int x, int y, int w, int h) const;

};


#endif //RAYCASTING_SCREEN_H
