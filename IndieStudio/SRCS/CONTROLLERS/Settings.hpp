/*
** EPITECH PROJECT, 2021
** sett
** File description:
** sett
*/

#ifndef BOMBERMAN_sett_HPP
#define BOMBERMAN_sett_HPP

#include <string>
#include <ENTITIES/WIDGETS/Button.hpp>
#include <IGraphic.hpp>
#include <ENTITIES/WIDGETS/Text.hpp>
#include "IEntitiesController.hpp"
#include "Sound.hpp"

class Settings : public IEntitiesController {
    int _offset;
    Event _event;
    int _selected_button;
    std::vector<Button> _buttons;
    std::vector<Text> _texts;
    Widget _background;
    float *_volume;
    float *_occupancy;
    IGraphic *_i_graphic;
public:
    Settings(float *volume, float *occupancy, IGraphic *i_graphic);
    ~Settings();
    std::vector<IEntities *> getEntities() override;
    std::vector<Collide *> getCollidable() override;
    Event update(Info *info) override;
};

#endif //BOMBERMAN_sett_HPP
