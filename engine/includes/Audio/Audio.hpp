/*
** EPITECH PROJECT, 2022
** AudioManager.hpp
** File description:
** Header for the audio management into the Engine
*/

#pragma once

#include "../../libs/Raylib/includes/Sound.hpp"
#include "../../libs/Raylib/includes/Music.hpp"

namespace Engine {
    class Audio {
        public:
            // Ctor
            Audio(const std::string &soundPath, const std::string &type);

            // Dtor
            ~Audio();

            // Functions for music parameters
            void play(void);
            void stop(void);
            void pause(void);
            void resume(void);
            bool isPlaying(void);
            void setVolume(float volume);
            void setPitch(float pitch);

        private:
            // Objects
            std::string &type;
            Raylib::Music _music;
            Raylib::Sound _sound;
    };
}