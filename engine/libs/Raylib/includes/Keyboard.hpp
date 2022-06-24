/*
** EPITECH PROJECT, 2022
** Text.hpp
** File description:
** Header for encapsulation of keyboard functions
*/

#pragma once

#include "Raylib.hpp"

namespace Raylib {
    class Keyboard {
        public:
            // Ctor
            Keyboard();

            // Dtor
            ~Keyboard();

            // Member functions
            int getKeyPressed(void);
            int getCharPressed(void);
            bool isKeyPressed(int key);
            bool isKeyDown(int key);
            bool isKeyReleased(int key);
            bool isKeyUp(int key);
    };
}
