/*
** EPITECH PROJECT, 2021
** Bomb
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(Vector3 position, std::vector <Model> *models, int length_ray) : Object("ASSETS/BOMB/skin.png", models, position),
                                                                            Collide(GetMeshBoundingBox(models->at(0).meshes[0]), _position)
{
    _ttl = 100;
    _no_collide = true;
    _animating = true;
    _length_ray = length_ray;
}

Bomb::~Bomb()
{
}

void Bomb::pack()
{
    std::string save;
    save = this->_path_texture + " " + std::to_string(this->_position.x) + " " + std::to_string(this->_position.y) + " " + 
    std::to_string(this->_position.z)+ " " + std::to_string(this->_ttl) + " " + std::to_string(this->_no_collide) + " " + std::to_string(this->_length_ray) +"\n";
    std::ofstream myfile("SAVE_DIR/Bomb_save", std::ios_base::app);
    if (myfile.is_open()) {
        myfile << save;
        myfile.close();
    }
    else
        std::cerr << "Unable to open file" << std::endl;
    myfile.close();
}

Bomb *Bomb::unpack(int nb, std::vector<Model> *models)
{
    std::ifstream myfile;
    std::vector<std::string> vect;
    myfile.open("SAVE_DIR/Bomb_save_tmp");
    std::string line;
    getline(myfile, line);
    std::istringstream ss(line);
    std::string ok;
    while (ss >> ok) {
        std::cout << "line " << line << " content" << ok << std::endl;
        vect.push_back(ok);
    }
    Vector3 pos;
    pos.x = std::stof(vect.at(1));
    pos.y = std::stof(vect.at(2));
    pos.z = std::stof(vect.at(3));
    auto b1 = new Bomb(pos, models, stoi(vect.at(6)));
    b1->_ttl = stoi(vect.at(4));
    b1->_no_collide = stoi(vect.at(5));
    delete_line("SAVE_DIR/Bomb_save_tmp", 0);
    myfile.close();
    return b1;
}

bool Bomb::checkExplosion(std::vector<Collide *> collidables, std::vector<Fire *> *fires, std::vector<Model> *models)
{
    if (_ttl != 0) {
        _ttl--;
        return (false);
    }

    Fire *fire;
    fire = new Fire({_position.x, _position.y, _position.z}, models);
    if (fire->doCollide(collidables))
        delete fire;
    else
        fires->push_back(fire);

    // + X
    for (int i = 1; i < _length_ray; i++) {
        fire = new Fire({_position.x + i * 2, _position.y, _position.z}, models);
        if (fire->doCollide(collidables)) {
            delete fire;
            break;
        }
        fires->push_back(fire);
    }

    // - X
    for (int i = 1; i < _length_ray; i++) {
        fire = new Fire({_position.x - i * 2, _position.y, _position.z}, models);
        if (fire->doCollide(collidables)) {
            delete fire;
            break;
        }
        fires->push_back(fire);
    }

    // + y
    for (int i = 1; i < _length_ray; i++) {
        fire = new Fire({_position.x, _position.y, _position.z + i * 2}, models);
        if (fire->doCollide(collidables)) {
            delete fire;
            break;
        }
        fires->push_back(fire);
    }

    // - y
    for (int i = 1; i < _length_ray; i++) {
        fire = new Fire({_position.x, _position.y, _position.z - i * 2}, models);
        if (fire->doCollide(collidables)) {
            delete fire;
            break;
        }
        fires->push_back(fire);
    }

    return (true);
}

void Bomb::destroy()
{
    _ttl = 0;
}
