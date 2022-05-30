/*
** EPITECH PROJECT, 2021
** Widget
** File description:
** Widget
*/

#ifndef BOMBERMAN_WIDGET_HPP
#define BOMBERMAN_WIDGET_HPP

#include <vector>
#include <string>
#include "IEntities.hpp"

class Widget : public IEntities {
protected:
    std::string _path_texture;
    Texture2D _texture_2_d;
    Image _image;
public:
    Rectangle _rect;
    Widget(std::string path_texture, Rectangle rect) {
        _rect = rect;
        _path_texture = path_texture;
        _image = LoadImage(_path_texture.c_str());
        _texture_2_d = LoadTextureFromImage(_image);
    };
    virtual ~Widget() {
        UnloadImage(_image);
        UnloadTexture(_texture_2_d);
    };
    void draw(Camera3D camera_3_d) override {
        DrawTexture(_texture_2_d, _rect.x, _rect.y, WHITE);
    };
};

#endif //BOMBERMAN_WIDGET_HPP
