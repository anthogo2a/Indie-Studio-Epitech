/*
** EPITECH PROJECT, 2021
** Hud
** File description:
** Hud
*/

#ifndef BOMBERMAN_HUD_HPP
#define BOMBERMAN_HUD_HPP

#include <IEntities.hpp>
#include <string>

class Hud : public IEntities {
    std::string _path_texture_alive;
    std::string _path_texture_dead;

    Texture2D _texture_2_d_alive;
    Texture2D _texture_2_d_dead;
    Image _image_alive;
    Image _image_dead;

    Rectangle _rect;
    Font _font;
    bool _dead;
    int _bomb;
    int _fire;
    int _speed;
    bool _wall_pass;
public:
    Hud(std::string path_texture_alive, std::string path_texture_dead, Rectangle rect) {
        _dead = false;
        _rect = rect;
        _bomb = _fire = _speed = 0;

        _font = LoadFontEx("ASSETS/Retroica.ttf", 96, nullptr, 0);

        _path_texture_alive = path_texture_alive;
        _path_texture_dead = path_texture_dead;
        _image_alive = LoadImage(_path_texture_alive.c_str());
        _image_dead = LoadImage(_path_texture_dead.c_str());
        _texture_2_d_alive = LoadTextureFromImage(_image_alive);
        _texture_2_d_dead = LoadTextureFromImage(_image_dead);
    };

    virtual ~Hud() {
        UnloadTexture(_texture_2_d_alive);
        UnloadTexture(_texture_2_d_dead);
    };

    void update(bool dead, int bomb, int fire, int speed, bool wall_pass) {
        _dead = dead;
        _bomb = bomb;
        _fire = fire;
        _speed = speed;
        _wall_pass = wall_pass;
    };

    void draw(Camera3D camera_3_d) override {
        Color txt_color(WHITE);

        if (!_dead) DrawTexture(_texture_2_d_alive, 0, 0, WHITE);
        else        DrawTexture(_texture_2_d_dead, 0, 0, WHITE);

        if (_rect.x <= 200) {
            DrawTextEx(_font, std::to_string(_bomb).c_str(), {_rect.x, _rect.y}, 20, 1.0f, txt_color);
            DrawTextEx(_font, std::to_string(_fire).c_str(), {_rect.x + 5, _rect.y + 25}, 20, 1.0f, txt_color);
            DrawTextEx(_font, std::to_string(_speed).c_str(), {_rect.x + 10, _rect.y + 50}, 20, 1.0f, txt_color);
            DrawTextEx(_font, std::to_string(_wall_pass).c_str(), {_rect.x + 15, _rect.y + 75}, 20, 1.0f, txt_color);
        } else {
            DrawTextEx(_font, std::to_string(_bomb).c_str(), {_rect.x, _rect.y}, 20, 1.0f, txt_color);
            DrawTextEx(_font, std::to_string(_fire).c_str(), {_rect.x - 5, _rect.y + 25}, 20, 1.0f, txt_color);
            DrawTextEx(_font, std::to_string(_speed).c_str(), {_rect.x - 10, _rect.y + 50}, 20, 1.0f, txt_color);
            DrawTextEx(_font, std::to_string(_wall_pass).c_str(), {_rect.x - 15, _rect.y + 75}, 20, 1.0f, txt_color);
        }
    };
};

#endif //BOMBERMAN_HUD_HPP
