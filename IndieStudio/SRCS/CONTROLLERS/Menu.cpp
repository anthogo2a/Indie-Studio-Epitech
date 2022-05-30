/*
** EPITECH PROJECT, 2021
** Menu
** File description:
** Menu
*/

#include <iostream>
#include "Menu.hpp"

Menu::Menu() : _background(Widget("ASSETS/BACKGROUND/menu.png", {0, 0, 1920, 1080}))
{
    _offset = 7;
    _event = NULL_EVENT;

    _selected_button = 0;
    _buttons.push_back(Button("START", "ASSETS/head.png", {800, 430, 0, 0}));
    _buttons[0]._state = Button::SELECTED;
    _buttons.push_back(Button("SETTINGS", "ASSETS/head.png", {800, 540,0, 0}));
    _buttons.push_back(Button("LOAD SAVE", "ASSETS/head.png", {800, 650, 0, 0}));
    _buttons.push_back(Button("EXIT", "ASSETS/head.png", {800, 760,0, 0}));
}

Menu::~Menu()
{
    _buttons.clear();
}

Event Menu::update(Info *info)
{
    if (_offset != 0) {
        _offset--;
        return NULL_EVENT;
    }

    info->tryConnect();

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
        if (does == "START") _event = KEYBIND;
        if (does == "SETTINGS") _event = SETTINGS;
        if (does == "LOAD SAVE") _event = LOAD_SAVE;
        if (does == "EXIT") _event = CLOSE_WINDOW;
        return (NULL_EVENT);
    }
    if (_event != NULL_EVENT) {
        Event event = _event;
        _event = NULL_EVENT;
        return (event);
    }
    return (NULL_EVENT);
}

std::vector<IEntities *> Menu::getEntities()
{
    std::vector<IEntities *> entities;

    entities.push_back(static_cast<IEntities *>(&_background));

    for (auto ite = _buttons.begin(); ite != _buttons.end(); ite++)
        entities.push_back(static_cast<IEntities *>(&*ite));
    return (entities);
}

std::vector<Collide *> Menu::getCollidable()
{
    return std::vector<Collide *>();
}