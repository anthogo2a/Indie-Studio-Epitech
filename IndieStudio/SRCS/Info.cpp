/*
** EPITECH PROJECT, 2021
** Info
** File description:
** Info
*/

#include <iostream>
#include "Info.hpp"
#include "raylib.h"

Info::Info() : _event(Event::NULL_EVENT)
{
    _keyboard_inputs.emplace_back(KeyboardInput(1));
    _keyboard_inputs.emplace_back(KeyboardInput(2));
    _keyboard_inputs.emplace_back(KeyboardInput(3));
    _keyboard_inputs.emplace_back(KeyboardInput(4));

    for (int i = 0; IsGamepadAvailable(i) && i < 4; i++) {
        _manette_inputs.emplace_back(ManetteInput(i));
    }
}

Info::~Info()
{
}

void Info::updateInfo()
{
    _event = Event::NULL_EVENT;
    if (WindowShouldClose()) {
        _event = Event::CLOSE_WINDOW;
        return;
    }

    std::vector<IInput *> inputs = getInputs();
    Event tmp_event;
    for (int i = 0; i < inputs.size(); i++) {
        if ((tmp_event = inputs[i]->press()) != NULL_EVENT) _event = tmp_event;
    }
}

Event Info::getEvent()
{
    return (_event);
}

std::vector<IInput *> Info::getInputs()
{
    std::vector<IInput *> inputs;
    for (auto ite = _keyboard_inputs.begin(); ite != _keyboard_inputs.end(); ite++)
        inputs.push_back(static_cast<IInput *>(&*ite));
    for (auto ite = _manette_inputs.begin(); ite != _manette_inputs.end(); ite++)
        inputs.push_back(static_cast<IInput *>(&*ite));
    return (inputs);
}

void Info::tryConnect()
{
    for (int i = _manette_inputs.size(); IsGamepadAvailable(i) && i < 4; i++) {
        _manette_inputs.emplace_back(ManetteInput(i));
    }
}


