/*
** EPITECH PROJECT, 2021
** Fire
** File description:
** Fire
*/

#include "Fire.hpp"

Fire::Fire(Vector3 position, std::vector<Model> *models) : Object("ASSETS/FIRE/skin.png", models, position),
                                                           Collide(GetMeshBoundingBox(models->at(0).meshes[0]), _position)
{
    _ttl = 40;
    _animating = true;
}

Fire::~Fire()
{
}

void Fire::pack()
{
    std::string save;
    save = this->_path_texture + " " + std::to_string(this->_position.x) + " " + std::to_string(this->_position.y) + " " + 
    std::to_string(this->_position.z) + " " + std::to_string(this->_ttl) + "\n";
    std::ofstream myfile("SAVE_DIR/Fire_save", std::ios_base::app);
    if (myfile.is_open()) {
        myfile << save;
        myfile.close();
    }
    else
        std::cerr << "Unable to open file" << std::endl;
    myfile.close();
}

Fire *Fire::unpack(int nb, std::vector<Model> *models)
{
    std::ifstream myfile;
    std::vector<std::string> vect;
    myfile.open("SAVE_DIR/Fire_save_tmp");
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
    auto f1 = new Fire(pos, models);
    f1->_ttl = stoi(vect.at(4));
    delete_line("SAVE_DIR/Fire_save_tmp", 0);
    myfile.close();
    return (f1);
}

bool Fire::checkFire()
{
    if (_ttl > 0) {
        _ttl--;
        return (false);
    }

    return (true);
}
