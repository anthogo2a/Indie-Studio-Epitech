/*
** EPITECH PROJECT, 2021
** Core
** File description:
** Core
*/

#include <iostream>
#include "Core.hpp"

Core::Core()
{
    InitAudioDevice();
    _volume = 0.4;
    _music = new Zic(&_volume, 0, "ASSETS/SOUND/music.mp3");
    _music->play_music();

    _running = true;
    _i_graphic = new Graphic();

    _occupancy = 0.8;

    _cur_controller = "MENU";
    auto game = new Game(&_volume, &_occupancy, _i_graphic->getModels());
    _i_entities_controllers["GAME"] = game;
    _i_entities_controllers["MENU"] = new Menu();
    _i_entities_controllers["PAUSE"] = new Pause();
    _i_entities_controllers["INPUT"] = new Input(game->getPlayers(), _i_graphic->getModels());
    _i_entities_controllers["SETTINGS"] = new Settings(&_volume, &_occupancy, _i_graphic);
    _i_entities_controllers["END"] = new End(&_volume, game->getPlayers());
}

void Core::handle_global_event(Event event)
{
    switch (event) {
        case Event::CLOSE_WINDOW:
            _running = false;
            break;
        case Event::GAME:
            dynamic_cast<Game *>(_i_entities_controllers.at("GAME"))->bot_generation();
            dynamic_cast<Game *>(_i_entities_controllers.at("GAME"))->map_generation();
            _cur_controller = "GAME";
            break;
        case Event::KEYBIND:
            _cur_controller = "INPUT";
            break;
        case Event::MENU:
            _music->play_music();
            if (_cur_controller == "PAUSE" || _cur_controller == "END") { // reset controllers
                delete dynamic_cast<Game *>(_i_entities_controllers.at("GAME"));
                _i_entities_controllers["GAME"] = new Game(&_volume, &_occupancy, _i_graphic->getModels());
                delete dynamic_cast<Input *>(_i_entities_controllers.at("INPUT"));
                _i_entities_controllers["INPUT"] = new Input(dynamic_cast<Game *>(_i_entities_controllers.at("GAME"))->getPlayers(), _i_graphic->getModels());
                delete dynamic_cast<End *>(_i_entities_controllers.at("END"));
                _i_entities_controllers["END"] = new End(&_volume, dynamic_cast<Game *>(_i_entities_controllers.at("GAME"))->getPlayers());
            }
            _cur_controller = "MENU";
            break;
        case Event::PAUSE_EVENT:
            if (_cur_controller == "GAME")
                _cur_controller = "PAUSE";
            break;
        case Event::SAVE:
            Game::Save::save(dynamic_cast<Game *>(_i_entities_controllers["GAME"]));
            break;
        case Event::SETTINGS:
            _cur_controller = "SETTINGS";
            break;
        case Event::END_GAME:
            _music->stop();
            _cur_controller = "END";
            break;
        case Event::LOAD_SAVE:
            if (!Game::Save::SaveExists()) return;
            Game::Save::loadSave(dynamic_cast<Game *>(_i_entities_controllers["GAME"]), _i_graphic->getModels());
            _cur_controller = "INPUT";
            break;
    }
}

int Core::mainLoop()
{
    Info *info;
    Event event;

    while (_running) {
        info = _i_graphic->getInfo();
        handle_global_event(info->getEvent());

        event = _i_entities_controllers[_cur_controller]->update(info);
        handle_global_event(event);

        std::vector<IEntities *> entities = _i_entities_controllers[_cur_controller]->getEntities();
        _i_graphic->drawEntities(entities);
        _music->update();
    }
    return (0);
}

Core::~Core()
{

    if (IsWindowFullscreen())
        _i_graphic->toggleFullscreen();
    CloseAudioDevice();
    for (auto ite = _i_entities_controllers.begin(); ite != _i_entities_controllers.end(); ite++)
        delete ite.operator*().second;
    delete _i_graphic;
    delete _music;
}

