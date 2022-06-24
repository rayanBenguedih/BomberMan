/*
** EPITECH PROJECT, 2022
** Mouse.hpp
** File description:
** Header for encapsulation of mouse functions
*/

#pragma once

#include "Raylib.hpp"

namespace Raylib {
    class Mouse {
        public:
            // Ctor
            Mouse();

            // Dtor
            ~Mouse();

            // Member functions
            bool isButtonPressed(int button);
            bool isButtonDown(int button);
            bool isButtonReleased(int button);
            bool isButtonUp(int button);
            Vector2 getPosition(void);
            int getX(void);
            int getY(void);
            void setPosition(int x, int y);
            void setOffset(int offsetX, int offsetY);
            void setScale(float scaleX, float scaleY);
            float getWheelMove(void);
            void setCursor(int cursor);
    };
}
