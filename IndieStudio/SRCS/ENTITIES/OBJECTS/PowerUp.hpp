/*
** EPITECH PROJECT, 2021
** PowerUp
** File description:
** PowerUp
*/

#ifndef BOMBERMAN_POWERUP_HPP
#define BOMBERMAN_POWERUP_HPP

#include "Player.hpp"

class PowerUp : public Object, public Collide, public Serialize {
    PowerUpTypes _type;
public:
    PowerUp(Vector3 position, std::vector<Model> * models, PowerUpTypes type);
    ~PowerUp();

    void pack() override;
    static PowerUp *unpack(int nb, std::vector<Model> *models);

    bool checkPowerUp(std::vector<Player *> players);
};

#endif //BOMBERMAN_POWERUP_HPP
