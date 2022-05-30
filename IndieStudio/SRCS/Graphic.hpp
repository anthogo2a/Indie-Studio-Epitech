/*
** EPITECH PROJECT, 2021
** Graphic
** File description:
** Graphic
*/

#ifndef BOMBERMAN_GRAPHIC_HPP
#define BOMBERMAN_GRAPHIC_HPP

#include <map>
#include <vector>

#include <ENTITIES/OBJECTS/Collide.hpp>
#include "Window.hpp"
#include "IGraphic.hpp"

class Graphic : public IGraphic {
    Window _window;
    Info *_info;
    Camera3D _camera;

    std::map<std::string, std::vector<Model> *> *_map_models;
//    std::map<std::string, std::vector<Texture2D> *> *_map_textures;
public:
    Graphic();
    ~Graphic();

    std::vector<Model> *loadModels(std::string models_path);
    std::map<std::string, std::vector<Model> *> *getModels();

    virtual void drawEntities(std::vector<IEntities *> i_entities) override;
    virtual Info *getInfo() override;
    virtual void toggleFullscreen() override;
};

#endif //BOMBERMAN_GRAPHIC_HPP
