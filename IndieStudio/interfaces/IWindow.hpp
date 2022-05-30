/*
** EPITECH PROJECT, 2021
** IWindow
** File description:
** IWindow
*/

#ifndef BOMBERMAN_IWINDOW_HPP
#define BOMBERMAN_IWINDOW_HPP

class IWindow {
public:
    virtual bool isOpen() = 0;
    virtual void close() = 0;
    virtual void toggleFullscreen() = 0;
};

#endif //BOMBERMAN_IWINDOW_HPP
