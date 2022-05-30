/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include "SRCS/Core.hpp"

int main()
{
    Core core = Core();

    int error_code = core.mainLoop();

    return (error_code);
}