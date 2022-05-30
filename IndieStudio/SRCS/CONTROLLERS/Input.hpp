/*
** EPITECH PROJECT, 2021
** Input
** File description:
** Input
*/

#ifndef BOMBERMAN_INPUT_HPP
#define BOMBERMAN_INPUT_HPP

#include <string>
#include <ENTITIES/WIDGETS/Button.hpp>
#include <ENTITIES/OBJECTS/Player.hpp>
#include "IEntitiesController.hpp"

class Input : public IEntitiesController {
    int _offset;
    Event _event;

    std::vector<Player *> *_players;

    int _selected_button;

    std::vector<Button> _buttons;
    Widget _background;
    std::vector<Widget *> _input_back;

    std::map<std::string, std::vector<Model> *> *_map_models;
public:
    Input(std::vector<Player *> *players, std::map<std::string, std::vector<Model> *> *map_models);
    ~Input();

    std::vector<IEntities *> getEntities() override;
    std::vector<Collide *> getCollidable() override;
    Event update(Info *info) override;

    void addPlayers(Info *info);
};

#endif //BOMBERMAN_INPUT_HPP
