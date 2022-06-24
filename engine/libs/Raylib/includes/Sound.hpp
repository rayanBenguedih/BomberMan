/*
** EPITECH PROJECT, 2022
** Sound.hpp
** File description:
** Header for encapsulation of sound functions
*/

#pragma once

#include "Raylib.hpp"
#include <string>

namespace Raylib {
    class Sound : public ::Sound {
        public:
            // Ctor
            Sound(const std::string &fileName);

            // Dtor
            ~Sound();

            // Member functions
            void unload(void);
            void play(void);
            void stop(void);
            void pause(void);
            void resume(void);
            bool isPlaying(void);
            void setVolume(float volume);
            void setPitch(float pitch);
    };
}
