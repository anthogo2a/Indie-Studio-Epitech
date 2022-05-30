/*
** EPITECH PROJECT, 2021
** Floor
** File description:
** Floor
*/

#ifndef BOMBERMAN_FLOOR_HPP
#define BOMBERMAN_FLOOR_HPP

#include <ENTITIES/Object.hpp>
#include "Serialize.hpp"

class Floor : public Object, public Serialize{
public:
    Floor(std::string path_texture, std::vector<Model> *models, Vector3 position) : Object(path_texture, models, position) {};
    ~Floor() {
        UnloadTexture(_textures_2d);
    };
    void pack() {
        std::string save;
        save = this->_path_texture + " " + std::to_string(this->_position.x) + " " + std::to_string(this->_position.y) + " " + 
        std::to_string(this->_position.z) + "\n";
        std::ofstream myfile("SAVE_DIR/Floor_save", std::ios_base::app);
        if (myfile.is_open()) {
            myfile << save;
            myfile.close();
        }
        else
            std::cerr << "Unable to open file" << std::endl;
        myfile.close();
    }
    static Floor *unpack(int nb, std::vector<Model> *models) {
        std::ifstream myfile;
        std::vector<std::string> vect;
        myfile.open("SAVE_DIR/Floor_save_tmp");
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
        auto f1 = new Floor(vect.at(0), models, pos);
        delete_line("SAVE_DIR/Floor_save_tmp", 0);
        myfile.close();
        return (f1);
    }
};

#endif //BOMBERMAN_FLOOR_HPP
