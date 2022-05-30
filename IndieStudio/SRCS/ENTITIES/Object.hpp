/*
** EPITECH PROJECT, 2021
** Object
** File description:
** Object
*/

#ifndef BOMBERMAN_OBJECT_HPP
#define BOMBERMAN_OBJECT_HPP

#include <vector>
#include <sstream>
#include "IEntities.hpp"

class Object : public IEntities {
protected:
    std::string _path_texture;
    Texture2D _textures_2d;

    int _pos_models;
    std::vector<Model> *_models;

    float _scale;
    float _direction;
    bool _animating;
    int _length_ray;
public:
    Object(std::string path_texture, std::vector<Model> *models, Vector3 position, float scale = 1);
    ~Object();
    void draw(Camera3D camera_3_d) override;
    Vector3 _position;
};

#endif //BOMBERMAN_OBJECT_HPP
