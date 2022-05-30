/*
** EPITECH PROJECT, 2021
** IEntities
** File description:
** IEntities
*/

#ifndef BOMBERMAN_IENTITIES_HPP
#define BOMBERMAN_IENTITIES_HPP

#include "raylib.h"

class IEntities {
public:
    virtual void draw(Camera3D camera_3_d) = 0;
};

#endif //BOMBERMAN_IENTITIES_HPP
