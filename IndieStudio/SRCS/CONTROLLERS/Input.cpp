/*
** EPITECH PROJECT, 2021
** Input
** File description:
** Input
*/

#include "Input.hpp"

Input::Input(std::vector<Player *> *players, std::map<std::string, std::vector<Model> *> *map_models) : _background(Widget("ASSETS/BACKGROUND/choose_player_back.png", {0, 0, 1920, 1080}))
{
    _map_models = map_models;

    _players = players;
    _offset = 10;
    _event = NULL_EVENT;


    _selected_button = 0;
    _buttons.push_back(Button("START", "ASSETS/head.png", {1550, 300, 0, 0}));
    _buttons[0]._state = Button::SELECTED;

    _input_back.push_back(new Widget("ASSETS/BACKGROUND/PLAYER/player_1_classic.png", {0, 0, 1920, 1080}));
    _input_back.push_back(new Widget("ASSETS/BACKGROUND/PLAYER/player_2_red.png", {0, 0, 1920, 1080}));
    _input_back.push_back(new Widget("ASSETS/BACKGROUND/PLAYER/player_3_vert.png", {0, 0, 1920, 1080}));
    _input_back.push_back(new Widget("ASSETS/BACKGROUND/PLAYER/player_4_black.png", {0, 0, 1920, 1080}));
    _input_back.push_back(new Widget("ASSETS/BACKGROUND/PLAYER/starting_max.png", {0, 0, 1920, 1080}));
}

Input::~Input()
{
    for (auto ite = _input_back.begin(); ite != _input_back.end(); ite++)
        delete ite.operator*();
}

Event Input::update(Info *info)
{
    addPlayers(info);

    if (_offset != 0) {
        _offset--;
        return NULL_EVENT;
    }
    for (auto ite = _players->begin(); ite != _players->end(); ite++) {
        if (ite.operator*()->getInput() && ite.operator*()->getInput()->getAction() == A_BUTTON) {
            std::string does = _buttons[_selected_button].press();
            _buttons[_selected_button]._state = Button::PRESSED;
            if (does == "START") _event = GAME;
            _offset = 10;
            return (NULL_EVENT);
        }
    }

    if (_event != NULL_EVENT) {
        Event event = _event;
        _event = NULL_EVENT;
        return (event);
    }
    return (NULL_EVENT);
}

std::vector<IEntities *> Input::getEntities()
{
    std::vector<IEntities *> entities;

    entities.push_back(static_cast<IEntities *>(&_background));

    int input_set_number = 0;
    for (int i = 0; i < _players->size(); i++) {
        if (_players->at(i)->getInput() != nullptr)
            input_set_number++;
    }
    entities.push_back(static_cast<IEntities *>(_input_back[input_set_number]));

    for (auto ite = _buttons.begin(); ite != _buttons.end(); ite++)
        entities.push_back(static_cast<IEntities *>(&*ite));
    return (entities);
}

std::vector<Collide *> Input::getCollidable()
{
    return std::vector<Collide *>();
}

void Input::addPlayers(Info *info)
{
    std::vector<std::string> textures{"skin_bomber_white.png", "skin_bomber_red.png", "skin_bomber_green.png", "skin_bomber_black.png"};
    std::vector<IInput *> inputs = info->getInputs();

    info->tryConnect();

    for (auto ite = _players->begin(); ite != _players->end(); ite++) {
        if (ite.operator*()->getInput() == nullptr) {
            for (auto ite_input = inputs.begin(); ite_input != inputs.end(); ite_input++) {
                if (ite_input.operator*()->isFree()) {
                    if (ite_input.operator*()->getAction() != NULL_ACTION) {
                        ite.operator*()->_ia = false;
                        ite.operator*()->setInput(ite_input.operator*());
                        ite_input.operator*()->linkPlayer(_players->size());
                        _offset = 10;
                    }
                }
            }
        }
    }

    for (auto ite = inputs.begin(); ite != inputs.end(); ite++) {
        if (ite.operator*()->isFree()) {
            if (ite.operator*()->getAction() != NULL_ACTION) {
                auto player = new Player("ASSETS/PLAYER/SKINS/" + textures[_players->size()], {5, 0, 0}, _map_models->at("Player"));
                player->setInput(ite.operator*());
                _players->push_back(player);
                ite.operator*()->linkPlayer(_players->size());
                _offset = 10;
            }
        }
    }
}
