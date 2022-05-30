/*
** EPITECH PROJECT, 2021
** Player
** File description:
** Player
*/

#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP

#include <vector>
#include <sstream>
#include <filesystem>
#include <utils.hpp>
#include <IInput.hpp>
#include <ENTITIES/WIDGETS/Hud.hpp>
#include "ENTITIES/Object.hpp"
#include "ENTITIES/OBJECTS/Collide.hpp"
#include "ENTITIES/OBJECTS/Serialize.hpp"
#include "Bomb.hpp"

class Player : public Object, public Serialize, public Collide {
    std::vector<Bomb *> *_bombs;

    IInput *_i_input;

    //stat
    int _length_ray;
    int _max_bombs;
    float _speed;
    bool _wall_pass;

    bool _waiting;
    int _bot_cool_down;

    float center_clip(const float pos);

    bool do_clip_on_axis(const float *offset_axis, float *new_position);
    Vector3 clipMovement(Action dir);
public:
    bool _ia;
    bool _dead;
    Action _tmp_action_bot;
    Action _dir_bomb;
    Player(std::string texture_path, Vector3 position, std::vector<Model> *models);
    ~Player();

    void pack() override;
    static Player *unpack(int nb, std::vector<Model> *models);

    void update(std::vector<Collide *> others, std::vector<Collide *> crates, std::vector<Collide *> bombs, Hud *hud);
    bool moveTo(Vector3 new_position, std::vector<Collide *> others, std::vector<Collide *> crates, std::vector<Collide *> bombs);
    void destroy();
    bool isAlive();
    void powerUp(PowerUpTypes type);

    void setInput(IInput *i_input);
    IInput *getInput();
    void updateBot(std::vector<Collide *> players, std::vector<Collide *> crates, std::vector<Collide *> walls, std::vector<Collide *> bombs);
    Action getActionBot();
    bool BotTryDir(Vector3 new_position, std::vector<Collide *> other);

    bool checkBombs(std::vector<Bomb *> *bombs, std::vector<Collide *> crates, std::vector<Model> *models);
};

#endif //BOMBERMAN_PLAYER_HPP
