/*
** EPITECH PROJECT, 2021
** Menu
** File description:
** Menu
*/

#ifndef BOMBERMAN_MENU_HPP
#define BOMBERMAN_MENU_HPP

#include <string>
#include <ENTITIES/WIDGETS/Button.hpp>
#include "IEntitiesController.hpp"

class Menu : public IEntitiesController {
    int _offset;
    Event _event;

    int _selected_button;
    std::vector<Button> _buttons;
    Widget _background;
public:
    Menu();
    ~Menu();

    std::vector<IEntities *> getEntities() override;
    std::vector<Collide *> getCollidable() override;
    Event update(Info *info) override;
};

#endif //BOMBERMAN_MENU_HPP
