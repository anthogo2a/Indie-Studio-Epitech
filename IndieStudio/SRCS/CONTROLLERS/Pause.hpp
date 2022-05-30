/*
** EPITECH PROJECT, 2021
** pause
** File description:
** pause
*/

#ifndef BOMBERMAN_pause_HPP
#define BOMBERMAN_pause_HPP

#include <string>
#include <ENTITIES/WIDGETS/Button.hpp>
#include "IEntitiesController.hpp"

class Pause : public IEntitiesController {
    int _offset;
    Event _event;
    int _selected_button;
    std::vector<Button> _buttons;
    Widget _background;
public:
    Pause();
    ~Pause();

    std::vector<IEntities *> getEntities() override;
    std::vector<Collide *> getCollidable() override;
    Event update(Info *info) override;
};

#endif //BOMBERMAN_pause_HPP
