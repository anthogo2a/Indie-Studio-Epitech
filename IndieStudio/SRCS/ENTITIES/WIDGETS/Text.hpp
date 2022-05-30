/*
** EPITECH PROJECT, 2021
** Text
** File description:
** Text
*/

#ifndef BOMBERMAN_TEXT_HPP
#define BOMBERMAN_TEXT_HPP

#include "ENTITIES/Widget.hpp"

class Text : public IEntities {
private:
    std::string _title;
    Rectangle _rect;
    Font _font;
public:
    Text(float *val, Rectangle rect);
    virtual ~Text();
    void updateText(float *val);
    void draw(Camera3D camera_3_d) override;
};

#endif //BOMBERMAN_TEXT_HPP
