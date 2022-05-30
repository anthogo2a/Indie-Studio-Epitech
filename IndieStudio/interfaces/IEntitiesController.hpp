/*
** EPITECH PROJECT, 2021
** IEntitiesController
** File description:
** IEntitiesController
*/

#ifndef BOMBERMAN_IENTITIESCONTROLLER_HPP
#define BOMBERMAN_IENTITIESCONTROLLER_HPP

#include "utils.hpp"
#include "Info.hpp"
#include "IEntities.hpp"
#include "ENTITIES/OBJECTS/Collide.hpp"

// interface for menu and game
class IEntitiesController {
public:
    virtual std::vector<IEntities *> getEntities() = 0;
    virtual std::vector<Collide *> getCollidable() = 0;
    virtual Event update(Info *info) = 0;
    virtual ~IEntitiesController() = default;
};

#endif //BOMBERMAN_IENTITIESCONTROLLER_HPP
