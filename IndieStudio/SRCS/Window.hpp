/*
** EPITECH PROJECT, 2021
** Window
** File description:
** Window
*/

#ifndef BOMBERMAN_WINDOW_HPP
#define BOMBERMAN_WINDOW_HPP

#include "../interfaces/IWindow.hpp"

#include <string>

class Window : public IWindow {
    bool _fullscreen;
public:
    Window(std::string title);
    ~Window();

    bool isOpen() override;
    void close() override;
    void toggleFullscreen() override;
};

#endif //BOMBERMAN_WINDOW_HPP
