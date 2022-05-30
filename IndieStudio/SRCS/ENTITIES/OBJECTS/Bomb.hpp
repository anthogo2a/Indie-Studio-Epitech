/*
** EPITECH PROJECT, 2021
** Bomb
** File description:
** Bomb
*/

#ifndef BOMBERMAN_BOMB_HPP
#define BOMBERMAN_BOMB_HPP

#include "ENTITIES/Object.hpp"
#include "Collide.hpp"
#include "Serialize.hpp"
#include "Fire.hpp"
#include "Wall.hpp"

class Bomb : public Object, public Collide, public Serialize {
public:
    int _ttl;
    Bomb(Vector3 position, std::vector<Model> *models, int length_ray);
    ~Bomb();

    bool checkExplosion(std::vector<Collide *> collidable, std::vector<Fire *> *_fires, std::vector<Model> *models);

    bool _no_collide;

    void destroy();

    void pack();
    static Bomb *unpack(int nb, std::vector<Model> *models);
};

#endif //BOMBERMAN_BOMB_HPP
