/*
** EPITECH PROJECT, 2021
** KeyboardInput
** File description:
** KeyboardInput
*/

#ifndef BOMBERMAN_KEYBOARDINPUT_HPP
#define BOMBERMAN_KEYBOARDINPUT_HPP

#include "IInput.hpp"
#include <map>

class KeyboardInput : public IInput {
    int _player_id;
    Action _action;
    std::map<int, Action> _maps;
    //  std::map<Action, T> _key_map; //link actions to keys
public:
    KeyboardInput(int map_id);
    Event press(); // return Event if key press correspond to global event

    void linkPlayer(int player_id);
    bool isFree() override;

    Action getAction();
};

#endif //BOMBERMAN_KEYBOARDINPUT_HPP
