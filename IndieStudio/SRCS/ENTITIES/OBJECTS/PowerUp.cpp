/*
** EPITECH PROJECT, 2021
** PowerUp
** File description:
** PowerUp
*/

#include <map>
#include "PowerUp.hpp"

const std::map<PowerUpTypes, std::string> types_assets = {
    {PowerUpTypes::BOMB_UP, "ASSETS/POWER/BombUp.png"},
    {PowerUpTypes::RANGE_UP, "ASSETS/POWER/RangeUp.png"},
    {PowerUpTypes::SPEED_UP, "ASSETS/POWER/SpeedUp.png"},
    {PowerUpTypes::WALL_PASS, "ASSETS/POWER/WallPass.png"},
};

PowerUp::PowerUp(Vector3 position, std::vector<Model> *models, PowerUpTypes type) :
                 Object(types_assets.at(type), models, position),
                 Collide(GetMeshBoundingBox(models->at(0).meshes[0]), _position)
{
    _type = type;
}

PowerUp::~PowerUp()
{
}

void PowerUp::pack()
{
    std::string save;
    save = this->_path_texture + " " + std::to_string(this->_position.x) + " " + std::to_string(this->_position.y) + " " + 
    std::to_string(this->_position.z) + " " + "\n";
    std::ofstream myfile("SAVE_DIR/PowerUp_save", std::ios_base::app);
    if (myfile.is_open()) {
        myfile << save;
        myfile.close();
    }
    else
        std::cerr << "Unable to open file" << std::endl;
    myfile.close();
}

// PowerUp *PowerUp::unpack(int nb, std::vector<Model> *models)
// {
//     std::ifstream myfile;
//     std::vector<std::string> vect;
//     myfile.open("SAVE_DIR/PowerUp_save");
//     std::string line;
//     getline(myfile, line);
//     std::istringstream ss(line);
//     std::string ok;
//     while (ss >> ok) {
//         vect.push_back(ok);
//     }
//     Vector3 pos;
//     pos.x = stoi(vect.at(1));
//     pos.y = stoi(vect.at(2));
//     pos.z = stoi(vect.at(3));
//     // TODO: Fix enum for constructor PowerUpTypes
//     // auto po1 = new PowerUp(pos, models,);
//     delete_line("SAVE_DIR/PowerUp_save", 0);
//     myfile.close();
//     return (po1);
// }

bool PowerUp::checkPowerUp(std::vector<Player *> players)
{
    for (auto ite = players.begin(); ite != players.end(); ite++) {
        if (doCollide(static_cast<Collide *>(ite.operator*()))) {
            ite.operator*()->powerUp(_type);
            return (true);
        }
    }
    return (false);
}
