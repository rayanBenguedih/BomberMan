/*
** EPITECH PROJECT, 2022
** Sound.hpp
** File description:
** Header for encapsulation of rectangle functions
*/

#pragma once

#include "Raylib.hpp"
#include "Color.hpp"

namespace Raylib {
class Rectangle : public ::Rectangle {
        public:
            // Ctor
            Rectangle(float x, float y, float width, float height, const Color&
            color);

            // Dtor
            ~Rectangle();

            // Member functions
            void draw(void);
            // TODO: Complete it with other functions

        private:
            Color _color;
    };
}