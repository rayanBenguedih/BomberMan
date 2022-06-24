/*
** EPITECH PROJECT, 2022
** Window.hpp
** File description:
** Encapsulation of window functions
*/

#include "../includes/Text.hpp"

#include <utility>

Raylib::Text::Text(std::string str, const Color &color) : _str(std::move(str)),
_size(20), _color(color)
{
}

Raylib::Text::~Text() = default;

const std::string &Raylib::Text::getStr() const
{
    return _str;
}

void Raylib::Text::setStr(const std::string &str)
{
    _str = str;
}

Raylib::Color Raylib::Text::getColor() const
{
    return _color;
}

void Raylib::Text::setColor(Raylib::Color &color)
{
    _color.r = color.r;
    _color.g = color.g;
    _color.b = color.b;
    _color.a = color.a;
}

unsigned int Raylib::Text::getSize() const
{
    return _size;
}

void Raylib::Text::setSize(int size)
{
    _size = size;
}

void Raylib::Text::draw(int x, int y)
{
    DrawText(_str.c_str(), x, y, _size, _color);
}