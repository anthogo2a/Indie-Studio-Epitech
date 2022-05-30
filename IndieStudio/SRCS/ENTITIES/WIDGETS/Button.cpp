/*
** EPITECH PROJECT, 2021
** Button
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(std::string title, std::string image_path, Rectangle rect) : Widget (image_path, rect), _title(title)
{
    _font = LoadFontEx("ASSETS/Retroica.ttf", 96, nullptr, 0);
    _state = NOT_SELECTED;
}

Button::Button(const Button &button) : Widget(button._path_texture, button._rect)
{
    _title = button._title;
    _font = LoadFontEx("ASSETS/Retroica.ttf", 96, nullptr, 0);
    _state = button._state;
}

void Button::draw(Camera3D camera_3_d)
{
    Color txt_color(WHITE);

    if (_state == SELECTED) {
        txt_color = PINK;
        DrawTexture(_texture_2_d, _rect.x - 100, _rect.y, WHITE);
    }
    if (_state == PRESSED) {
        txt_color = BLUE;
        DrawTexture(_texture_2_d, _rect.x - 80, _rect.y, WHITE);
    }
    DrawTextEx(_font, _title.c_str(), {_rect.x, _rect.y}, 80, 1.0f, txt_color);
}

std::string Button::press()
{
    return (_title);
}

Button::~Button()
{
    UnloadFont(_font);
    UnloadTexture(_texture_2_d);
}