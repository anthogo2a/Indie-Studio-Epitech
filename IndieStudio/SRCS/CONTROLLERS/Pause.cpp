/*
** EPITECH PROJECT, 2021
** Menu
** File description:
** Menu
*/

#include "Pause.hpp"

Pause::Pause() : _background(Widget("ASSETS/BACKGROUND/pause.png", {0, 0, 960, 540}))
{
    _offset = 7;
    _event = NULL_EVENT;

    _selected_button = 0;
    _buttons.push_back(Button("RESUME", "ASSETS/head.png", {800, 400, 0, 0}));
    _buttons[0]._state = Button::SELECTED;
    _buttons.push_back(Button("SAVE", "ASSETS/head.png", {800, 510, 0, 0}));
    _buttons.push_back(Button("EXIT", "ASSETS/head.png", {800, 620,0, 0}));
}

Pause::~Pause()
{
    _buttons.clear();
}

Event Pause::update(Info *info)
{
    if (_offset != 0) {
        _offset--;
        return NULL_EVENT;
    }

    Action action = NULL_ACTION;
    for (int i = 0; i < info->getInputs().size(); i++) {
        if (info->getInputs()[i]->getAction() != NULL_ACTION) {
            action = info->getInputs()[i]->getAction();
            _offset = 7;
        }
    }

    if (action == DOWN) {
        _buttons[_selected_button]._state = Button::NOT_SELECTED;
        _selected_button = (_selected_button + 1) % _buttons.size();
        _buttons[_selected_button]._state = Button::SELECTED;
    }
    if (action == UP) {
        _buttons[_selected_button]._state = Button::NOT_SELECTED;
        _selected_button = (_selected_button - 1) % _buttons.size();
        _buttons[_selected_button]._state = Button::SELECTED;
    }
    if (action == A_BUTTON) {
        std::string does = _buttons[_selected_button].press();
        _buttons[_selected_button]._state = Button::PRESSED;
        if (does == "RESUME") _event = GAME;
        if (does == "SAVE") _event = SAVE;
        if (does == "EXIT") _event = MENU;
        return (NULL_EVENT);
    }
    if (_event != NULL_EVENT) {
        Event event = _event;
        _event = NULL_EVENT;
        return (event);
    }
    return (NULL_EVENT);
}

std::vector<IEntities *> Pause::getEntities()
{
    std::vector<IEntities *> entities;

    entities.push_back(static_cast<IEntities *>(&_background));

    for (auto ite = _buttons.begin(); ite != _buttons.end(); ite++)
        entities.push_back(static_cast<IEntities *>(&*ite));
    return (entities);
}

std::vector<Collide *> Pause::getCollidable()
{
    return (std::vector<Collide *>());
}