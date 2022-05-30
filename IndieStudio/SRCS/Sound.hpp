/*
** EPITECH PROJECT, 2021
** Sound
** File description:
** Sound
*/

#ifndef BOMBERMAN_SOUND_HPP
#define BOMBERMAN_SOUND_HPP

#include <string>
#include "raylib.h"

class Zic {
    public:
        Zic(float *volume, int play_time, std::string path);
        ~Zic();
        Music music;
        void play_music();
        void stop();
        void update();
        float *_volume;
        int _play_time;
    protected:
    private:
};

#endif /* !BOMBERMAN_SOUND_HPP */
