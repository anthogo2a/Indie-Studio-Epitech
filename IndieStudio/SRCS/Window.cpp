/*
** EPITECH PROJECT, 2021
** Window
** File description:
** Window
*/

#include "raylib.h"
#include "Window.hpp"

const int screenWidth = 1920;
const int screenHeight = 1080;
const int frameRate = 60;

Window::Window(std::string title)
{
    InitWindow(screenWidth, screenHeight, title.c_str());

    SetTargetFPS(frameRate);
}

bool Window::isOpen()
{
    return (!WindowShouldClose());
}

void Window::close()
{
    CloseWindow();
}

Window::~Window()
{
    close();
}

void Window::toggleFullscreen()
{
    ToggleFullscreen();
}