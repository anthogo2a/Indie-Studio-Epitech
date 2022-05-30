/*
** EPITECH PROJECT, 2021
** End
** File description:
** End
*/

#include <Sound.hpp>
#include "End.hpp"

End::End(float *volume, std::vector<Player *> *players) : _background(Widget("ASSETS/BACKGROUND/end.png", {0, 0, 1920, 1080}))
{
    _players = players;
    _offset = 10;

    _volume = volume;
    _music = new Zic(_volume, 0, "ASSETS/SOUND/win.wav");
    _music->play_music();

    _selected_button = 0;
    _buttons.push_back(Button("CONTINUE...", "ASSETS/head.png", {1300, 920, 0, 0}));
    _buttons[0]._state = Button::SELECTED;

    _win_back.push_back(new Widget("ASSETS/WIN/classic_win.png", {0, 0, 1920, 1080}));
    _win_back.push_back(new Widget("ASSETS/WIN/red_win.png", {0, 0, 1920, 1080}));
    _win_back.push_back(new Widget("ASSETS/WIN/green_win.png", {0, 0, 1920, 1080}));
    _win_back.push_back(new Widget("ASSETS/WIN/red_win.png", {0, 0, 1920, 1080}));
}

End::~End()
{
    for (auto ite = _win_back.begin(); ite != _win_back.end(); ite++)
        delete ite.operator*();
    _buttons.clear();
    delete _music;
}

Event End::update(Info *info)
{
    _music->play_music();
    _music->update();

    if (_offset != 0) {
        _offset--;
        return NULL_EVENT;
    }
    for (auto ite = _players->begin(); ite != _players->end(); ite++) {
        if (ite.operator*()->getInput() && ite.operator*()->getInput()->getAction() == A_BUTTON) {
            std::string does = _buttons[_selected_button].press();
            _buttons[_selected_button]._state = Button::PRESSED;
            if (does == "CONTINUE...") _event = MENU;
            _offset = 10;
            return (NULL_EVENT);
        }
    }

    if (_event != NULL_EVENT) {
        Event event = _event;
        _event = NULL_EVENT;
        _music->stop();
        return (event);
    }
    return (NULL_EVENT);
}

std::vector<IEntities *> End::getEntities()
{
    std::vector<IEntities *> entities;

    entities.push_back(static_cast<IEntities *>(&_background));

    int winner = 0;
    for (int i = 0; i != _players->size(); i++) {
        if (!_players->at(i)->_dead)
            winner = i;
        if (!_players->at(i)->_ia && !_players->at(i)->_dead) {
            winner = i;
            break;
        }
    }

    entities.push_back(static_cast<IEntities *>(_win_back[winner]));

    for (auto ite = _buttons.begin(); ite != _buttons.end(); ite++)
        entities.push_back(static_cast<IEntities *>(&*ite));
    return (entities);
}

std::vector<Collide *> End::getCollidable()
{
    return std::vector<Collide *>();
}

