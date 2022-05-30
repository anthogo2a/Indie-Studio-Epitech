/*
** EPITECH PROJECT, 2021
** ManetteInput
** File description:
** ManetteInput
*/

#ifndef BOMBERMAN_MANETTEINPUT_HPP
#define BOMBERMAN_MANETTEINPUT_HPP

#include "IInput.hpp"
#include <map>

#define PS3_NAME_ID         "PLAYSTATION(R)3 Controller"

class ManetteInput : public IInput {
    int _player_id;
    Action _action;

    int _manette_id;
    //  std::map<Action, T> _key_map; //link actions to keys
public:
    ManetteInput(int manette_id);
    Event press(); // return Event if key press correspond to global event

    void linkPlayer(int player_id);
    bool isFree() override;

    Action getAction();
};

#endif //BOMBERMAN_MANETTEINPUT_HPP
