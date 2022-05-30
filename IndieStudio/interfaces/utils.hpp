/*
** EPITECH PROJECT, 2021
** utils
** File description:
** utils
*/

#ifndef BOMBERMAN_UTILS_HPP
#define BOMBERMAN_UTILS_HPP

enum PowerUpTypes {
    SPEED_UP,
    BOMB_UP,
    RANGE_UP,
    WALL_PASS,
};

// input Event
enum Action {
    DOWN,
    UP,
    LEFT,
    RIGHT,
    A_BUTTON,
    B_BUTTON,
    PAUSE,
    NULL_ACTION
};

enum Event {
    END_GAME,
    CLOSE_WINDOW,
    PAUSE_EVENT,
    KEYBIND,
    LOAD_SAVE,
    SAVE,
    SETTINGS,
    MENU,
    GAME,
    NULL_EVENT
};

#endif //BOMBERMAN_UTILS_HPP
