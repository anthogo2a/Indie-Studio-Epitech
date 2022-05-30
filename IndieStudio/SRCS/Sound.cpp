/*
** EPITECH PROJECT, 2021
** sound
** File description:
** soudn
*/

#include "Sound.hpp"

Zic::Zic(float *volume, int play_time, std::string path)
{
    _play_time = play_time;
    music = LoadMusicStream(path.c_str());
    _volume = volume;
}

void Zic::play_music()
{
    PlayMusicStream(music);
    SetMusicVolume(music, *_volume);
}

void Zic::stop()
{
    StopMusicStream(music);
}

void Zic::update()
{
    UpdateMusicStream(music);

    int timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music)*400;

    if (_play_time != 0 && timePlayed > _play_time) StopMusicStream(music);
}

Zic::~Zic()
{
    UnloadMusicStream(music);
}
