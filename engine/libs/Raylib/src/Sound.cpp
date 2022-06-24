/*
** EPITECH PROJECT, 2022
** Sound.hpp
** File description:
** Header for encapsulation of sound functions
*/

#include "../includes/Sound.hpp"

Raylib::Sound::Sound(const std::string &fileName)
{
    ::Sound sound = LoadSound(fileName.c_str());
    stream = sound.stream;
    frameCount = sound.frameCount;
}

Raylib::Sound::~Sound()
{
    unload();
}

void Raylib::Sound::play()
{
    PlaySound(*this);
}

void Raylib::Sound::stop()
{
    StopSound(*this);
}

void Raylib::Sound::pause()
{
    PauseSound(*this);
}

void Raylib::Sound::resume()
{
    ResumeSound(*this);
}

bool Raylib::Sound::isPlaying()
{
    return IsSoundPlaying(*this);
}

void Raylib::Sound::setVolume(float volume)
{
    SetSoundVolume(*this, volume);
}

void Raylib::Sound::setPitch(float pitch)
{
    SetSoundPitch(*this, pitch);
}

void Raylib::Sound::unload()
{
    UnloadSound(*this);
}