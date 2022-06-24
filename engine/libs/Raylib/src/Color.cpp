/*
** EPITECH PROJECT, 2022
** Color.cpp
** File description:
** Encapsulation of color functions
*/

#include "../includes/Color.hpp"

Raylib::Color::Color(unsigned char r, unsigned char g, unsigned char b,
                     unsigned char a) : ::Color{r, g, b, a}
{
}

Raylib::Color::Color(const Raylib::Color &other)
{
    r = other.r;
    g = other.g;
    b = other.b;
    a = other.a;
}

Raylib::Color &Raylib::Color::operator=(const Raylib::Color &other)
{
    r = other.r;
    g = other.g;
    b = other.b;
    a = other.a;
    return *this;
}

Raylib::Color::~Color() = default;
