/*
** EPITECH PROJECT, 2021
** Object
** File description:
** Object
*/

#include <iostream>
#include <raymath.h>
#include "Object.hpp"

Object::Object(std::string path_texture, std::vector<Model> *models, Vector3 position, float scale) : _position(position), _path_texture(path_texture), _models(models), _direction(0.0f), _scale(scale)
{
    _animating = false;
    _pos_models = 0;

    if (!_path_texture.empty())
        _textures_2d = LoadTexture(_path_texture.c_str());
}

Object::~Object()
{
    UnloadTexture(_textures_2d);
}

void Object::draw(Camera3D camera_3_d)
{
    BeginMode3D(camera_3_d);

    if (!_path_texture.empty())
        _models->at(_pos_models).materials[0].maps[MAP_DIFFUSE].texture = _textures_2d;
    _models->at(_pos_models).transform = MatrixRotateXYZ({DEG2RAD * 0,DEG2RAD * _direction,DEG2RAD * 0 });

    DrawModel(_models->at(_pos_models), _position, _scale, WHITE);
    EndMode3D();

    if (_animating) {
        _pos_models++;
        if (_pos_models == _models->size()) _pos_models = 0;
    }
}
