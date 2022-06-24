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
    class Music : public ::Music {
    public:
        // Ctor
        explicit Music(const std::string &fileName);

        // Dtor
        ~Music();

        // Member functions
        void unload(void);
        void play(void);
        void update(void);
        void stop(void);
        void pause(void);
        void resume(void);
        bool isPlaying(void);
        void setVolume(float volume);
    };
}
