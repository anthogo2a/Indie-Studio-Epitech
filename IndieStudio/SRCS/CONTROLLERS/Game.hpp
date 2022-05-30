/*
** EPITECH PROJECT, 2021
** Game
** File description:
** Game
*/

#ifndef BOMBERMAN_GAME_HPP
#define BOMBERMAN_GAME_HPP

#include <ENTITIES/Widget.hpp>
#include <ENTITIES/OBJECTS/Bomb.hpp>
#include "ENTITIES/OBJECTS/Player.hpp"
#include "ENTITIES/OBJECTS/Fire.hpp"
#include "ENTITIES/OBJECTS/Floor.hpp"
#include "ENTITIES/OBJECTS/Crate.hpp"
#include <ENTITIES/OBJECTS/PowerUp.hpp>
#include <ENTITIES/OBJECTS/Floor.hpp>
#include <ENTITIES/WIDGETS/Hud.hpp>
#include <Sound.hpp>
#include "ENTITIES/OBJECTS/Wall.hpp"
#include "IEntitiesController.hpp"

class Game : public IEntitiesController {
protected:
    std::vector<Floor *> _floors;
    std::vector<Player *> _players;
    std::vector<Wall *> _walls;
    std::vector<Crate *> _crates;
    std::vector<Bomb *> _bombs;
    std::vector<Fire *> _fires;
    std::vector<PowerUp *> _power_ups;

    std::vector<Hud *> _huds;
    Widget _background;

    std::map<std::string, std::vector<Model> *> *_map_models;

    std::map<std::string, Zic *> _effects;
    float *_volume;
    float *_occupancy;
public:
    class Save;
    Game(float *volume, float *occupancy, std::map<std::string, std::vector<Model> *> *map_models);
    ~Game();

    void map_generation();
    std::vector<IEntities *> getEntities() override;
    std::vector<Collide *> getCollidable() override;
    std::vector<Serialize *> getSerializable();
    Event update(Info *info) override;

    std::vector<Player *> *getPlayers();
    void bot_generation();
private:
    std::vector<Vector3>
    genRandomPos(int width, int height, float left, float top);

    template<typename T, typename M>
    std::vector<T> vect_cast(std::vector<M> vector);
};

#endif //BOMBERMAN_GAME_HPP
