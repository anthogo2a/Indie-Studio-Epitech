/*
** EPITECH PROJECT, 2021
** KeyboardInput
** File description:
** KeyboardInput
*/

#include <map>
#include <iostream>
#include "KeyboardInput.hpp"
#include "raylib.h"

KeyboardInput::KeyboardInput(int map_id)
{
    _player_id = -1;
    _action = NULL_ACTION;

    switch (map_id) {
        case 1:
            _maps = std::map<int, Action> {
                {KEY_ENTER,  A_BUTTON},
                {KEY_UP,     UP},
                {KEY_DOWN,   DOWN},
                {KEY_RIGHT,  RIGHT},
                {KEY_LEFT,   LEFT},
                {KEY_P,      PAUSE},
                {KEY_ESCAPE, PAUSE},
            }; // input set map #1
            break;
        case 2:
            _maps = std::map<int, Action> {
                {KEY_Q,      A_BUTTON},
                {KEY_W,      UP},
                {KEY_S,      DOWN},
                {KEY_D,      RIGHT},
                {KEY_A,      LEFT},
                {KEY_P,      PAUSE},
                {KEY_ESCAPE, PAUSE},
            }; // input set map #2
            break;
        case 3:
            _maps = std::map<int, Action> {
                {KEY_R,      A_BUTTON},
                {KEY_T,      UP},
                {KEY_G,      DOWN},
                {KEY_H,      RIGHT},
                {KEY_F,      LEFT},
                {KEY_P,      PAUSE},
                {KEY_ESCAPE, PAUSE},
            }; // input set map #3
            break;
        case 4:
            _maps = std::map<int, Action> {
                {KEY_U,      A_BUTTON},
                {KEY_I,      UP},
                {KEY_K,      DOWN},
                {KEY_L,      RIGHT},
                {KEY_J,      LEFT},
                {KEY_P,      PAUSE},
                {KEY_ESCAPE, PAUSE},
            }; // input set map #4
            break;
    }
}

void KeyboardInput::linkPlayer(int player_id)
{
    _player_id = player_id;
}

Event KeyboardInput::press()
{
    _action = NULL_ACTION;

    for (std::map<int, Action>::iterator ite = _maps.begin(); ite != _maps.end(); ite++) {
        if (IsKeyPressed(ite->first) || (ite->second != A_BUTTON && IsKeyDown(ite->first)))
            _action = ite->second;
    }

    if (_action == PAUSE) return PAUSE_EVENT;
    return (NULL_EVENT);
}

Action KeyboardInput::getAction()
{
    return (_action);
}

bool KeyboardInput::isFree()
{
    if (_player_id != -1)
        return (false);
    return (true);
}
