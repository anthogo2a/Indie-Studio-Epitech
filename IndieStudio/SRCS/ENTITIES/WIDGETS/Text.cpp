/*
** EPITECH PROJECT, 2021
** Text
** File description:
** Text
*/

#include "Text.hpp"

Text::Text(float *val, Rectangle rect)
{
    _title = std::to_string((int)(*val * 10));
    _font = LoadFontEx("ASSETS/Retroica.ttf", 96, nullptr, 0);
    _rect = rect;
}

void Text::draw(Camera3D camera_3_d)
{
    Color txt_color(WHITE);

    DrawTextEx(_font, _title.c_str(), {_rect.x, _rect.y}, 80, 1.0f, txt_color);
}

Text::~Text()
{
}

void Text::updateText(float *val)
{
    _title = std::to_string((int)(*val * 10));
}
