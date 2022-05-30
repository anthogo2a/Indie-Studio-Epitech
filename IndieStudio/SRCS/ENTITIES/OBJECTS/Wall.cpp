/*
** EPITECH PROJECT, 2021
** Wall
** File description:
** Wall
*/

#include "Wall.hpp"

Wall::Wall(std::string path_texture, Vector3 position, std::vector<Model> *models) : Object(path_texture, models, position, 1),
                                                           Collide(GetMeshBoundingBox(models->at(0).meshes[0]), _position)
{
    _animating = false;
}

Wall::~Wall()
{
}

void Wall::pack()
{
    std::string save;
    save = this->_path_texture + " " + std::to_string(this->_position.x) + " " + std::to_string(this->_position.y) + " " + 
    std::to_string(this->_position.z) + "\n";
    std::ofstream myfile("SAVE_DIR/Wall_save", std::ios_base::app);
    if (myfile.is_open()) {
        myfile << save;
        myfile.close();
    }
    else
        std::cerr << "Unable to open file" << std::endl;
    myfile.close();
}

Wall *Wall::unpack(int nb, std::vector<Model> *models)
{
    std::ifstream myfile;
    std::vector<std::string> vect;
    myfile.open("SAVE_DIR/Wall_save_tmp");
    std::string line;
    getline(myfile, line);
    std::istringstream ss(line);
    std::string ok;
    while (ss >> ok)
        vect.push_back(ok);
    Vector3 pos;
    pos.x = std::stof(vect.at(1));
    pos.y = std::stof(vect.at(2));
    pos.z = std::stof(vect.at(3));
    auto w1 = new Wall(vect.at(0), pos, models);
    delete_line("SAVE_DIR/Wall_save_tmp", 0);
    myfile.close();
    return w1;
}