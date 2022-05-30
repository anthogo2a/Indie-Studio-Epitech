/*
** EPITECH PROJECT, 2021
** Graphic
** File description:
** Graphic
*/

#include "raylib.h"
#include "Graphic.hpp"
#include "ENTITIES/OBJECTS/Player.hpp"

Graphic::Graphic() : _window("Bomberman")
{
    _camera = {0};
    _camera.position = {0.0f, 37.0f, 10.0f};  // Camera position
    _camera.target = {0.0f, 0.0f, 0.0f};      // Camera looking at point
    _camera.up = {0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
    _camera.fovy = 45.0f;                                          // Camera field-of-view Y
    _camera.projection = CAMERA_PERSPECTIVE;                       // Camera mode type

    SetCameraMode(_camera, CAMERA_FREE);              // Set a free camera mode

    _info = new Info();

    _map_models = new std::map<std::string, std::vector<Model> *>;
    (*_map_models)["Player"] = loadModels("ASSETS/PLAYER/MODELS/bomberman_");
    (*_map_models)["Crate"] = loadModels("ASSETS/CRATE/MODELS/crate_");
    (*_map_models)["Wall"] = loadModels("ASSETS/WALL/MODELS/crate_");
    (*_map_models)["Bomb"] = loadModels("ASSETS/BOMB/MODELS/bomb_");
    (*_map_models)["Fire"] = loadModels("ASSETS/FIRE/MODELS/fire_");
    (*_map_models)["Power"] = loadModels("ASSETS/POWER/MODELS/power_");
    (*_map_models)["Floor"] = loadModels("ASSETS/FLOOR/MODELS/floor_");

//    _map_textures = new std::map<std::string, std::vector<Texture2D> *>;
//    (*_map_textures)[""] = loadModels("");
    //TODO maybe map of texture

    SetExitKey(-1);
}

void Graphic::drawEntities(std::vector<IEntities *> i_entities)
{
    UpdateCamera(&_camera);

    BeginDrawing();

    ClearBackground(BLACK);

    for (int i = 0; i < i_entities.size(); i++)
        i_entities[i]->draw(_camera);
    // 
    EndDrawing();
}

Info *Graphic::getInfo()
{
    _info->updateInfo();

    return (_info);
}

std::vector<Model> *Graphic::loadModels(std::string models_path)
{
    size_t count_file = 0;
    std::string dir = models_path;
    dir.erase(dir.rfind('/'));

    for (auto const & file : std::filesystem::directory_iterator(dir)) count_file++;

    auto models = new std::vector<Model>(count_file / 2);

    for (size_t i = 1; i < (count_file / 2) + 1; i++) {
        std::stringstream filename;
        filename << models_path.c_str();
        filename.fill('0');
        filename.width(6);
        filename << i << ".obj";
        models->at(i - 1) = LoadModel(filename.str().c_str());
    }

    return (models);
}

std::map<std::string, std::vector<Model> *> *Graphic::getModels()
{
    return (_map_models);
}

void Graphic::toggleFullscreen()
{
    _window.toggleFullscreen();
}

Graphic::~Graphic()
{
    for (auto ite = _map_models->begin(); ite != _map_models->end(); ite++) {
        for (auto ite2 = ite->second->begin(); ite2 != ite->second->end(); ite2++)
            UnloadModel(ite2.operator*());
    }
    delete _info;
}
