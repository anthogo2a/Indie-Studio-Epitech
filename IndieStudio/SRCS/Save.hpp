/*
** EPITECH PROJECT, 2021
** save_file
** File description:
** save_file
*/

#ifndef BOMBERMAN_SAVE_HPP
#define BOMBERMAN_SAVE_HPP

#include "CONTROLLERS/Game.hpp"

class Game::Save {
public:
    static void save(Game *game);
    static bool SaveExists();
    static void loadSave(Game *game, std::map<std::string, std::vector<Model> *> *map_models);
};

#endif /* !BOMBERMAN_SAVE_HPP */