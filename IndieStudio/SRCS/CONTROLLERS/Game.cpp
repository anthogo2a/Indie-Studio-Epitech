/*
** EPITECH PROJECT, 2021
** Game
** File description:
** Game
*/

#include "Game.hpp"
#include <algorithm>

Game::Game(float *volume, float *occupancy, std::map<std::string, std::vector<Model> *> *map_models) : _background(Widget("ASSETS/BACKGROUND/game.png", {0, 0, 1920, 1080}))
{
    _map_models = map_models;
    _occupancy = occupancy;

    _volume = volume;
    _effects["Bomb"] = new Zic(_volume, 200, "ASSETS/SOUND/bomb.wav");
    _effects["PowerUp"] = new Zic(_volume, 200, "ASSETS/SOUND/powerup.wav");
    _effects["Die"] = new Zic(_volume, 200, "ASSETS/SOUND/bomb.wav");
    _effects["DropBomb"] = new Zic(_volume, 200, "ASSETS/SOUND/drop_bomb.wav");
    _effects["Dead"] = new Zic(_volume, 200, "ASSETS/SOUND/dead.wav");

    _huds.push_back(new Hud("ASSETS/HUD/ALIVE/classic.png", "ASSETS/HUD/DEAD/classic.png", {85, 40, 0, 0}));
    _huds.push_back(new Hud("ASSETS/HUD/ALIVE/red.png", "ASSETS/HUD/DEAD/red.png", {1815, 945, 0, 0}));
    _huds.push_back(new Hud("ASSETS/HUD/ALIVE/green.png", "ASSETS/HUD/DEAD/green.png", {1815, 40, 0, 0}));
    _huds.push_back(new Hud("ASSETS/HUD/ALIVE/black.png", "ASSETS/HUD/DEAD/black.png", {85, 945, 0, 0}));
}

Game::~Game()
{
    for (auto ite = _crates.begin(); ite != _crates.end(); ite++)
        delete ite.operator*();
    for (auto ite = _walls.begin(); ite != _walls.end(); ite++)
        delete ite.operator*();
    for (auto ite = _floors.begin(); ite != _floors.end(); ite++)
        delete ite.operator*();
    for (auto ite = _bombs.begin(); ite != _bombs.end(); ite++)
        delete ite.operator*();
    for (auto ite = _huds.begin(); ite != _huds.end(); ite++)
        delete ite.operator*();
    for (auto ite = _effects.begin(); ite != _effects.end(); ite++)
        delete ite->second;
    for (auto ite = _players.begin(); ite != _players.end(); ite++) {
        if (ite.operator*()->getInput())
            ite.operator*()->getInput()->linkPlayer(-1);
    }
    for (auto ite = _players.begin(); ite != _players.end(); ite++)
        delete ite.operator*();
}

Event Game::update(Info *info)
{
    int i = 0;

    for (auto ite = _effects.begin(); ite != _effects.end(); ite++)
        ite->second->update();

    int nb_alive = 0, nb_ia = 0;
    for (auto ite = _players.begin(); ite != _players.end(); i++, ite++) {
        if (!ite.operator*()->_dead) nb_alive++;
        if (ite.operator*()->_ia && !ite.operator*()->_dead) {
            nb_ia++;
            ite.operator*()->updateBot(vect_cast<Collide *>(_players), vect_cast<Collide *>(_crates), vect_cast<Collide *>(_walls), vect_cast<Collide *>(_bombs));
        }
        ite.operator*()->update(vect_cast<Collide *>(_walls), vect_cast<Collide *>(_crates), vect_cast<Collide *>(_bombs), _huds[i]);
        if (ite.operator*()->checkBombs(&_bombs, vect_cast<Collide *>(_crates), _map_models->at("Bomb")))
            _effects["DropBomb"]->play_music();
    }
    if (nb_alive <= 1 || nb_alive == nb_ia) return (Event::END_GAME);

    for (int i = 0; i < _bombs.size(); i++) {
        if (_bombs[i]->checkExplosion(vect_cast<Collide *>(_walls), &_fires, _map_models->at("Fire"))) {
            _bombs.erase(_bombs.begin() + i);
            _effects["Bomb"]->play_music();
        }
    }

    for (int  i = 0; i < _crates.size(); i++) {
        if (_crates[i]->checkCrate(&_power_ups, _map_models))
            _crates.erase(_crates.begin() + i);
    }

    for (int  i = 0; i < _power_ups.size(); i++) {
        if (_power_ups[i]->checkPowerUp(_players)) {
            _power_ups.erase(_power_ups.begin() + i);
            _effects["PowerUp"]->play_music();
        }
    }

    for (int  i = 0; i < _fires.size(); i++) {
        for (auto ite = _bombs.begin(); ite != _bombs.end(); ite++) {
            if (_fires[i]->doCollide(ite.operator*()))
                ite.operator*()->destroy();
        }

        for (auto ite = _crates.begin(); ite != _crates.end(); ite++) {
            if (_fires[i]->doCollide(ite.operator*()))
                ite.operator*()->destroy();
        }

        for (auto ite = _players.begin(); ite != _players.end(); ite++) {
            if (_fires[i]->doCollide(ite.operator*())) {
                ite.operator*()->destroy();
                _effects["Dead"]->play_music();
            }
        }

        if (_fires[i]->checkFire())
            _fires.erase(_fires.begin() + i);
    }

    return (NULL_EVENT);
}

std::vector<IEntities *> Game::getEntities()
{
    std::vector<IEntities *> entities;

    entities.push_back(static_cast<IEntities *>(&_background));

    for (auto ite = _players.begin(); ite != _players.end(); ite++) {
        if (ite.operator*()->isAlive())
            entities.push_back(static_cast<IEntities *>(*ite));
    }
    for (auto ite = _walls.begin(); ite != _walls.end(); ite++)
        entities.push_back(static_cast<IEntities *>(*ite));
    for (auto ite = _crates.begin(); ite != _crates.end(); ite++)
        entities.push_back(static_cast<IEntities *>(*ite));
    for (auto ite = _bombs.begin(); ite != _bombs.end(); ite++)
        entities.push_back(static_cast<IEntities *>(*ite));
    for (auto ite = _fires.begin(); ite != _fires.end(); ite++)
        entities.push_back(static_cast<IEntities *>(*ite));
    for (auto ite = _power_ups.begin(); ite != _power_ups.end(); ite++)
        entities.push_back(static_cast<IEntities *>(*ite));
    for (auto ite = _floors.begin(); ite != _floors.end(); ite++)
        entities.push_back(static_cast<IEntities *>(*ite));
    for (auto ite = _huds.begin(); ite != _huds.end(); ite++)
        entities.push_back(static_cast<IEntities *>(*ite));
    return (entities);
}

std::vector<Collide *> Game::getCollidable()
{
    std::vector<Collide *> entities;

    for (auto ite = _walls.begin(); ite != _walls.end(); ite++)
        entities.push_back(static_cast<Collide *>(*ite));
    for (auto ite = _crates.begin(); ite != _crates.end(); ite++)
        entities.push_back(static_cast<Collide *>(*ite));
    for (auto ite = _bombs.begin(); ite != _bombs.end(); ite++)
        entities.push_back(static_cast<Collide *>(*ite));
    return (entities);
}

std::vector<Serialize *> Game::getSerializable()
{
    std::vector<Serialize *> serializable;

    for (auto ite = _players.begin(); ite != _players.end(); ite++)
        serializable.push_back(static_cast<Serialize *>(*ite));
    for (auto ite = _bombs.begin(); ite != _bombs.end(); ite++)
        serializable.push_back(static_cast<Serialize *>(*ite));
    for (auto ite = _walls.begin(); ite != _walls.end(); ite++)
        serializable.push_back(static_cast<Serialize *>(*ite));
    for (auto ite = _crates.begin(); ite != _crates.end(); ite++)
        serializable.push_back(static_cast<Serialize *>(*ite));
    for (auto ite = _fires.begin(); ite != _fires.end(); ite++)
        serializable.push_back(static_cast<Serialize *>(*ite));
    for (auto ite = _floors.begin(); ite != _floors.end(); ite++)
        serializable.push_back(static_cast<Serialize *>(*ite));

    return (serializable);
}

std::vector<Player *> *Game::getPlayers()
{
    return (&_players);
}

void Game::map_generation()
{
    if (!_walls.empty()) return;

    int width = 17, height = 11; // width should always be unpair

    float max_top = -1 * ((float)height + 1);
    float max_left = -1 * ((float)width + 1);

    for (int i = 0; i < width + 2; i++)
        _walls.push_back(new Wall("ASSETS/WALL/skin.png", {max_left + i * 2, 0, max_top}, _map_models->at("Wall")));
    for (int i = 0; i < width + 2; i++)
        _walls.push_back(new Wall("ASSETS/WALL/skin.png", {max_left + i * 2, 0, max_top + (height + 1) * 2}, _map_models->at("Wall")));

    for (int i = 0; i < height; i++)
        _walls.push_back(new Wall("ASSETS/WALL/skin.png", {max_left, 0, max_top + (i + 1) * 2}, _map_models->at("Wall")));
    for (int i = 0; i < height; i++)
        _walls.push_back(new Wall("ASSETS/WALL/skin.png", {max_left + (width + 1) * 2, 0, max_top + (i + 1) * 2}, _map_models->at("Wall")));

    for (int i = 1; i < width; i++) {
        for (int o = 1; o < height; o++) {
            if ((i + 1)% 2 == 0 || (o+1) % 2 == 0) continue;
            _walls.push_back(new Wall("ASSETS/WALL/skin2.png", {max_left + i * 2, 0, max_top + o * 2}, _map_models->at("Wall")));
        }
    }

    std::vector<Vector3> corners {
        {max_left + 2, 0, max_top + 2},
        {max_left + width * 2, 0, max_top + height * 2},
        {max_left + width * 2, 0, max_top + 2},
        {max_left + 2, 0, max_top + height * 2},
    };

    std::vector<Vector3> random_positions = genRandomPos(width, height, max_left, max_top);
    for (auto ite = random_positions.begin(); ite != random_positions.end(); ite++)
        _crates.push_back(new Crate(ite.operator*(), _map_models->at("Crate")));

    for (int i = 0; i < width + 2; i++) {
        for (int o = 0; o < height + 2; o++) {
            if ((i%2) == o%2)
                _floors.push_back(new Floor("ASSETS/FLOOR/skin1.png", _map_models->at("Floor"), {max_left + i * 2, 0, max_top + o * 2}));
            else
                _floors.push_back(new Floor("ASSETS/FLOOR/skin2.png", _map_models->at("Floor"), {max_left + i * 2, 0, max_top + o * 2}));
        }
    }

    for (int i = 0; i < _players.size(); i++)
        _players[i]->moveTo(corners[i], std::vector<Collide *>(),std::vector<Collide *>(), vect_cast<Collide *>(_bombs));
}

std::vector<Vector3> Game::genRandomPos(int width, int height, float max_left, float max_top)
{
    std::vector<std::pair<float, float>> poss;

    for (int i = 1; i < width + 1; i++) {
        for (int o = 1; o < height; o++) {
            if (i % 2 == 0 || (o+1) % 2 == 0) continue;
            poss.push_back({max_left + i * 2, max_top + o * 2});
        }
    }

    for (int i = 1; i < width + 1; i++) {
        for (int o = 1; o < height + 1; o++) {
            if (o % 2 == 0) continue;
            poss.push_back({max_left + i * 2, max_top + o * 2});
        }
    }

    std::vector<std::pair<float, float>> corners {
        {max_left + 2, max_top + 2}, {max_left + 2, max_top + 4}, {max_left + 4, max_top + 2},
        {max_left + width * 2, max_top + height * 2}, {max_left + width * 2 - 2, max_top + height * 2}, {max_left + width * 2, max_top + height * 2 - 2},
        {max_left + width * 2, max_top + 2}, {max_left + width * 2 - 2, max_top + 2}, {max_left + width * 2, max_top + 4},
        {max_left + 2, max_top + height * 2}, {max_left + 4, max_top + height * 2}, {max_left + 2, max_top + height * 2 - 2},
    };

    std::pair<float, float> corner;
    for (auto i = 0; i < corners.size(); i++) {
        corner = corners[i];
        poss.erase(std::find(poss.begin(), poss.end(), corner));
    }

    int to_delete = poss.size() * (1 - *_occupancy);
    for (int i = 0; i < to_delete; i++)
        poss.erase(poss.begin() + std::rand() % poss.size());

    std::vector<Vector3> vector;
    for (int i = 0; i < poss.size(); i++)
        vector.push_back({poss[i].first, 0, poss[i].second});

    return (vector);
}

template<typename T, typename M>
std::vector<T> Game::vect_cast(std::vector<M> vector)
{
    std::vector<T> entities;

    for (auto ite = vector.begin(); ite != vector.end(); ite++)
        entities.push_back(static_cast<T>(*ite));

    return (entities);
}

void Game::bot_generation()
{
    std::vector<Action> defaults {DOWN, UP, DOWN, UP};
    std::vector<std::string> textures {"skin_bomber_white.png", "skin_bomber_red.png", "skin_bomber_green.png", "skin_bomber_black.png"};

    for (int i = 0; i < _players.size(); i++) {
        if (_players[i]->getInput() == nullptr) {
            _players[i]->_ia = true;
            _players[i]->_tmp_action_bot = defaults[i];
        }
    }

    for (int i = _players.size(); i < 4; i++) {
        _players.push_back(new Player("ASSETS/PLAYER/SKINS/" + textures[_players.size()], {5, 0, 0}, _map_models->at("Player")));
        _players.back()->_ia = true;
        _players.back()->_tmp_action_bot = defaults[_players.size() - 1];
    }
}
