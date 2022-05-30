/*
** EPITECH PROJECT, 2021
** Menu
** File description:
** Menu
*/

#include "Settings.hpp"
#include <sstream>
#include <iostream>
#include "raylib.h"

Settings::Settings(float *volume, float *occupancy, IGraphic *i_graphic) : _background(Widget("ASSETS/BACKGROUND/settings.png", {0, 0, 960, 540}))
{
    _offset = 7;
    _event = NULL_EVENT;

    _volume = volume;
    _i_graphic = i_graphic;

    _occupancy = occupancy;

    std::ostringstream ss;
    std::string s(ss.str());
    _selected_button = 0;

    _buttons.push_back(Button("SOUND DOWN", "ASSETS/head.png", {150, 530, 0, 0}));
    _buttons[0]._state = Button::SELECTED;  
    _buttons.push_back(Button("SOUND UP", "ASSETS/head.png", {1200, 530, 0, 0}));
    _buttons.push_back(Button("MORE BOX", "ASSETS/head.png", {200, 640, 0, 0}));
    _buttons.push_back(Button("LESS BOX", "ASSETS/head.png", {1200, 640, 0, 0}));
    _buttons.push_back(Button("Fullscreen ON/OFF", "ASSETS/head.png", {600, 800,0, 0}));
    _buttons.push_back(Button("RETURN", "ASSETS/head.png", {800, 950,0, 0}));

    _texts.push_back(Text(_occupancy, {900, 640, 0, 0}));
    _texts.push_back(Text(_volume, {900, 530, 0, 0}));
}

Settings::~Settings()
{
    _buttons.clear();
    _texts.clear();
}

Event Settings::update(Info *info)
{
    _texts[0].updateText(_occupancy);
    _texts[1].updateText(_volume);

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
        if (does == "SOUND UP" && *_volume < 1) (*_volume) += 0.1;
        if (does == "SOUND DOWN" && *_volume > 0) (*_volume) -= 0.1;
        if (does == "MORE BOX" && *_occupancy < 1) (*_occupancy) += 0.1;
        if (does == "LESS BOX" && *_occupancy > 0) (*_occupancy) -= 0.1;
        if (does == "Fullscreen ON/OFF") _i_graphic->toggleFullscreen();
        if (does == "RETURN") _event = MENU;
        return (NULL_EVENT);
    }
    if (_event != NULL_EVENT) {
        Event event = _event;
        _event = NULL_EVENT;
        return (event);
    }
    return (NULL_EVENT);

}

std::vector<IEntities *> Settings::getEntities()
{
    std::vector<IEntities *> entities;

    entities.push_back(static_cast<IEntities *>(&_background));

    for (auto ite = _buttons.begin(); ite != _buttons.end(); ite++)
        entities.push_back(static_cast<IEntities *>(&*ite));
    for (auto ite = _texts.begin(); ite != _texts.end(); ite++)
        entities.push_back(static_cast<IEntities *>(&*ite));
    return (entities);
}

std::vector<Collide *> Settings::getCollidable()
{
    return std::vector<Collide *>();
}