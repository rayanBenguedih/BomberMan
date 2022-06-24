/*
** EPITECH PROJECT, 2022
** Gamepad.hpp
** File description:
** Header for encapsulation of gamepad functions
*/

#pragma once

#include "Raylib.hpp"
#include <string>

namespace Raylib {
    class Gamepad {
        public:
            // Ctor
            explicit Gamepad(int gamepad);

            // Dtor
            ~Gamepad();

            // Member functions
            bool isAvailable(void);
            std::string getName(void);
            bool isButtonPressed(int button);
            bool isButtonDown(int button);
            bool isButtonReleased(int button);
            bool isButtonUp(int button);
            int getButtonPressed(void);
            int getAxisCount(void);
            float getAxisMovement(int axis);
            int setMappings(const char *mappings);

        private:
            int _gamepad;
    };
}
