/*
** EPITECH PROJECT, 2021
** Fire
** File description:
** Fire
*/

#ifndef BOMBERMAN_FIRE_HPP
#define BOMBERMAN_FIRE_HPP

#include <ENTITIES/Object.hpp>
#include "Collide.hpp"
#include "Serialize.hpp"

class Fire : public Object, public Collide, public Serialize {
    int _ttl;
public:
    Fire(Vector3 position, std::vector<Model> *models);
    ~Fire();

    void pack() override;
    static Fire *unpack(int nb, std::vector<Model> *models);

    bool checkFire();
};

#endif //BOMBERMAN_FIRE_HPP
