/*
** EPITECH PROJECT, 2022
** Sound.hpp
** File description:
** Header for encapsulation of sound functions
*/

#include "../includes/Music.hpp"

Raylib::Music::Music(const std::string &fileName)
{
    ::Music music = LoadMusicStream(fileName.c_str());
    ctxType = music.ctxType;
    ctxData = music.ctxData;
    looping = music.looping;
    frameCount = music.frameCount;
    stream = music.stream;
}

Raylib::Music::~Music()
{
    unload();
}

void Raylib::Music::play()
{
    PlayMusicStream(*this);
}

void Raylib::Music::update()
{
    UpdateMusicStream(*this);
}

void Raylib::Music::stop()
{
    StopMusicStream(*this);
}

void Raylib::Music::pause()
{
    PauseMusicStream(*this);
}

void Raylib::Music::resume()
{
    ResumeMusicStream(*this);
}

bool Raylib::Music::isPlaying()
{
    return IsMusicStreamPlaying(*this);
}

void Raylib::Music::setVolume(float volume)
{
    SetMusicVolume(*this, volume);
}

void Raylib::Music::unload()
{
    if (stream.buffer) {
        UnloadMusicStream(*this);
    }
}