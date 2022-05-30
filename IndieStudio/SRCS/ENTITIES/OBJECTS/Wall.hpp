/*
** EPITECH PROJECT, 2021
** Wall
** File description:
** Wall
*/

#ifndef BOMBERMAN_WALL_HPP
#define BOMBERMAN_WALL_HPP

#include "ENTITIES/Object.hpp"
#include "Collide.hpp"
#include "Serialize.hpp"

class Wall : public Object, public Serialize, public Collide {
public:
    Wall(std::string path_texture, Vector3 position, std::vector<Model> *models);
    ~Wall();

    void pack() override;
    static Wall *unpack(int nb, std::vector<Model> *models);
};

#endif //BOMBERMAN_WALL_HPP
