/*
** EPITECH PROJECT, 2021
** Button
** File description:
** Button
*/

#ifndef BOMBERMAN_BUTTON_HPP
#define BOMBERMAN_BUTTON_HPP

#include "ENTITIES/Widget.hpp"

class Button : public Widget {
private:
    std::string _title;
    Font _font;
public:
    enum STATE {
        NOT_SELECTED,
        SELECTED,
        PRESSED
    };
    STATE _state;
    Button(std::string title, std::string image_path, Rectangle rect);
    Button(const Button &button);
    virtual ~Button();
    void draw(Camera3D camera_3_d) override;
    std::string press();
};

#endif //BOMBERMAN_BUTTON_HPP
