/*
** EPITECH PROJECT, 2021
** IInput
** File description:
** IInput
*/

#ifndef BOMBERMAN_IINPUT_HPP
#define BOMBERMAN_IINPUT_HPP

#include "vector"
#include "utils.hpp"

class IInput {
    int _player_id = 0; // to link inputs to players
public:
    virtual Event press() = 0; // return Event if key press correspond to global event

    virtual void linkPlayer(int player_id) = 0;
    virtual bool isFree() = 0;

    virtual Action getAction() = 0;
};

#endif //BOMBERMAN_IINPUT_HPP
