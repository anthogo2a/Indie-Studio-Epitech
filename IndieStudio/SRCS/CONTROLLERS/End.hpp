/*
** EPITECH PROJECT, 2021
** End
** File description:
** End
*/

#ifndef BOMBERMAN_END_HPP
#define BOMBERMAN_END_HPP

#include <ENTITIES/OBJECTS/Player.hpp>
#include <ENTITIES/WIDGETS/Button.hpp>
#include "IEntitiesController.hpp"

class End : public IEntitiesController {
    std::vector<Player *> *_players;

    int _offset;
    int _selected_button;
    std::vector<Button> _buttons;

    Widget _background;
    std::vector<Widget *> _win_back;

    Event _event;
    Zic *_music;
    float *_volume;
public:
    End(float *volume, std::vector<Player *> *players);
    ~End();

    std::vector<IEntities *> getEntities() override;
    std::vector<Collide *> getCollidable() override;
    Event update(Info *info) override;
};

#endif //BOMBERMAN_END_HPP
