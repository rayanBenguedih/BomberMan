/*
** EPITECH PROJECT, 2022
** Rectangle.cpp
** File description:
** Encapsulation of rectangle functions
*/

#include "../includes/Rectangle.hpp"

Raylib::Rectangle::Rectangle(float x, float y, float width, float height,
                             const Color& color) : ::Rectangle{x, y, width, height}, _color(color)
{
}

Raylib::Rectangle::~Rectangle() = default;

void Raylib::Rectangle::draw()
{
    DrawRectangle(static_cast<int>(x), static_cast<int>(y),
                  static_cast<int>(width), static_cast<int>(height),
                  _color);
}