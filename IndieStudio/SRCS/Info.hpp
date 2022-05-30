/*
** EPITECH PROJECT, 2021
** Info
** File description:
** Info
*/

#ifndef BOMBERMAN_INFO_HPP
#define BOMBERMAN_INFO_HPP

#include <utils.hpp>
#include <INPUTS/KeyboardInput.hpp>
#include <INPUTS/ManetteInput.hpp>

class Info {
    Event _event;
    std::vector<KeyboardInput> _keyboard_inputs;
    std::vector<ManetteInput> _manette_inputs;
public:
    Info();
    ~Info();
    void updateInfo();

    Event getEvent();
    std::vector<IInput *> getInputs();

    void tryConnect();
};

#endif //BOMBERMAN_INFO_HPP
