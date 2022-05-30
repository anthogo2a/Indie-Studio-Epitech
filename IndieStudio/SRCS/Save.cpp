/*
** EPITECH PROJECT, 2021
** Save
** File description:
** savez
*/

#include "Save.hpp"

void Game::Save::save(Game *game)
{
    std::vector<Serialize *> serializable = game->getSerializable();

    remove("SAVE_DIR/Player_save");
    remove("SAVE_DIR/Bomb_save");
    remove("SAVE_DIR/Wall_save");
    remove("SAVE_DIR/Crate_save");
    remove("SAVE_DIR/Fire_save");
    remove("SAVE_DIR/Floor_save");
    for (auto ite = serializable.begin(); ite != serializable.end(); ite++)
        ite.operator*()->pack();
}

void Game::Save::loadSave(Game *game, std::map<std::string, std::vector<Model> *> *map_models)
{
    if (std::filesystem::exists("SAVE_DIR/Player_save")) {
        std::filesystem::copy("SAVE_DIR/Player_save", "SAVE_DIR/Player_save_tmp");
        while (!Serialize::isEmpty("SAVE_DIR/Player_save_tmp"))
            game->_players.push_back(Player::unpack(game->_players.size(), map_models->at("Player")));
        remove("SAVE_DIR/Player_save_tmp");
    }

    if (std::filesystem::exists("SAVE_DIR/Bomb_save")) {
        std::filesystem::copy("SAVE_DIR/Bomb_save", "SAVE_DIR/Bomb_save_tmp");
        while (!Serialize::isEmpty("SAVE_DIR/Bomb_save_tmp"))
            game->_bombs.push_back(Bomb::unpack(game->_bombs.size(), map_models->at("Bomb")));
        remove("SAVE_DIR/Bomb_save_tmp");
    }

    if (std::filesystem::exists("SAVE_DIR/Wall_save")) {
        std::filesystem::copy("SAVE_DIR/Wall_save", "SAVE_DIR/Wall_save_tmp");
        while (!Serialize::isEmpty("SAVE_DIR/Wall_save_tmp"))
            game->_walls.push_back(Wall::unpack(game->_walls.size(), map_models->at("Wall")));
        remove("SAVE_DIR/Wall_save_tmp");
    }

    if (std::filesystem::exists("SAVE_DIR/Crate_save")) {
        std::filesystem::copy("SAVE_DIR/Crate_save", "SAVE_DIR/Crate_save_tmp");
        while (!Serialize::isEmpty("SAVE_DIR/Crate_save_tmp"))
            game->_crates.push_back(Crate::unpack(game->_crates.size(), map_models->at("Crate")));
        remove("SAVE_DIR/Crate_save_tmp");
    }

    if (std::filesystem::exists("SAVE_DIR/Fire_save")) {
        std::filesystem::copy("SAVE_DIR/Fire_save", "SAVE_DIR/Fire_save_tmp");
        while (!Serialize::isEmpty("SAVE_DIR/Fire_save_tmp"))
            game->_fires.push_back(Fire::unpack(game->_fires.size(), map_models->at("Fire")));
        remove("SAVE_DIR/Fire_save_tmp");
    }

    if (std::filesystem::exists("SAVE_DIR/Floor_save")) {
        std::filesystem::copy("SAVE_DIR/Floor_save", "SAVE_DIR/Floor_save_tmp");
        while (!Serialize::isEmpty("SAVE_DIR/Floor_save_tmp"))
            game->_floors.push_back(Floor::unpack(game->_floors.size(), map_models->at("Floor")));
        remove("SAVE_DIR/Floor_save_tmp");
    }
}


bool Game::Save::SaveExists()
{
    return (!Serialize::isEmpty("SAVE_DIR/Player_save"));
}
