/*
** EPITECH PROJECT, 2022
** Color.hpp
** File description:
** Header for encapsulation of color functions
*/

#pragma once

#include "Raylib.hpp"

namespace Raylib {
    class Color : public ::Color {
    public:
        // Ctor
        Color(unsigned char r, unsigned char g, unsigned char b, unsigned
        char a);
        Color(const Color &);

        // Dtor
        ~Color();

        // Member functions
        // TODO: Complete it with other functions

        // Operators
        Color& operator=(const Color &);
    };
}