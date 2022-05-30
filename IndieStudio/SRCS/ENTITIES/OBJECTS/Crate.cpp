/*
** EPITECH PROJECT, 2021
** Crate
** File description:
** Crate
*/

#include <raymath.h>
#include "Crate.hpp"

Crate::Crate(Vector3 position, std::vector<Model> *models) : Object("ASSETS/CRATE/skin.png", models, position, 1),
                                                             Collide(GetMeshBoundingBox(models->at(0).meshes[0]), _position)
{
    _animating = false;
}

Crate::~Crate()
{
}

void Crate::destroy()
{
    _animating = true;
}

void Crate::pack()
{
    std::string save;
    save = this->_path_texture + " " + std::to_string(this->_position.x) + " " + std::to_string(this->_position.y) + " " +
    std::to_string(this->_position.z) +  " " + std::to_string(this->_animating) + " " + std::to_string(this->_pos_models) + " " + "\n";
    std::ofstream myfile("SAVE_DIR/Crate_save", std::ios_base::app);
    if (myfile.is_open()) {
        myfile << save;
        myfile.close();
    }
    else
        std::cerr << "Unable to open file" << std::endl;
    myfile.close();
}

Crate *Crate::unpack(int nb, std::vector<Model> *models)
{
    std::ifstream myfile;
    std::vector<std::string> vect;
    myfile.open("SAVE_DIR/Crate_save_tmp");
    std::string line;
    getline(myfile, line);
    std::istringstream ss(line);
    std::string ok;
    while (ss >> ok) {
        vect.push_back(ok);
    }
    Vector3 pos;
    pos.x = std::stof(vect.at(1));
    pos.y = std::stof(vect.at(2));
    pos.z = std::stof(vect.at(3));
    auto c1 = new Crate(pos, models);
    c1->_animating = stoi(vect.at(4));
    c1->_pos_models = stoi(vect.at(5));
    delete_line("SAVE_DIR/Crate_save_tmp", 0);
    myfile.close();
    return (c1);
}


bool Crate::checkCrate(std::vector<PowerUp *> *power_ups, std::map<std::string, std::vector<Model> *> *models_map)
{
    if (!_animating) return (false);

    if (_pos_models != _models->size() - 1) {
        return (false);
    }

    int drop_rate = 1;
    int rand;
    std::vector<PowerUpTypes> types = {PowerUpTypes::WALL_PASS, PowerUpTypes::BOMB_UP, PowerUpTypes::SPEED_UP, PowerUpTypes::RANGE_UP};
    if ((std::rand() % 10) <= drop_rate) {
        rand = std::rand() % 10;
        if (rand < 1) {
            power_ups->push_back(new PowerUp(_position, models_map->at("Power"), types[0]));
            return (true);
        }
        if (rand < 3) {
            power_ups->push_back(new PowerUp(_position, models_map->at("Power"), types[1]));
            return (true);
        }
        if (rand < 5) {
            power_ups->push_back(new PowerUp(_position, models_map->at("Power"), types[2]));
            return (true);
        }
        power_ups->push_back(new PowerUp(_position, models_map->at("Power"), types[3]));
    }
    return (true);
    // 10 % wall pass
    // 20 % bomb up
    // 20 % speed up
    // 50 % fire up
}