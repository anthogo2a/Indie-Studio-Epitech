/*
** EPITECH PROJECT, 2021
** Core
** File description:
** Core
*/

#ifndef BOMBERMAN_CORE_HPP
#define BOMBERMAN_CORE_HPP

#include "Graphic.hpp"
#include "CONTROLLERS/Menu.hpp"
#include "CONTROLLERS/Game.hpp"
#include "CONTROLLERS/Pause.hpp"
#include "CONTROLLERS/Settings.hpp"
#include "CONTROLLERS/Input.hpp"
#include "CONTROLLERS/End.hpp"
#include "Sound.hpp"
#include "Save.hpp"

class Core
{
    bool _running;
    IGraphic *_i_graphic;

    std::string _cur_controller;
    std::map<std::string, IEntitiesController *> _i_entities_controllers;

    Zic *_music;
    float _volume;
    float _occupancy;
public:
    Core();
    virtual ~Core();
    int mainLoop();
    void handle_global_event(Event event);
};

#endif //BOMBERMAN_CORE_HPP
