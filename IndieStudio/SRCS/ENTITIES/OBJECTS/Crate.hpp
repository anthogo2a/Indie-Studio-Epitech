/*
** EPITECH PROJECT, 2021
** Crate
** File description:
** Crate
*/

#ifndef BOMBERMAN_CRATE_HPP
#define BOMBERMAN_CRATE_HPP

#include <vector>
#include <sstream>
#include <filesystem>
#include <utils.hpp>
#include <map>
#include "ENTITIES/Object.hpp"
#include "ENTITIES/OBJECTS/Collide.hpp"
#include "PowerUp.hpp"

class Crate : public Object, public Serialize, public Collide {
public:
    Crate(Vector3 position, std::vector<Model> *models);
    ~Crate();

    void destroy();

    void pack();
    static Crate *unpack(int nb, std::vector<Model> *models);

    bool checkCrate(std::vector<PowerUp *> *power_ups, std::map<std::string, std::vector<Model> *> *models_map);
};


#endif //BOMBERMAN_CRATE_HPP
