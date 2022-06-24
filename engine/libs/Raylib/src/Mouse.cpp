/*
** EPITECH PROJECT, 2022
** Mouse.cpp
** File description:
** Header for encapsulation of mouse functions
*/

#include "../includes/Mouse.hpp"

Raylib::Mouse::Mouse()
{
}

Raylib::Mouse::~Mouse() = default;

bool Raylib::Mouse::isButtonPressed(int button)
{
    return IsMouseButtonPressed(button);
}

bool Raylib::Mouse::isButtonDown(int button)
{
    return IsMouseButtonDown(button);
}

bool Raylib::Mouse::isButtonReleased(int button)
{
    return IsMouseButtonReleased(button);
}

bool Raylib::Mouse::isButtonUp(int button)
{
    return IsMouseButtonUp(button);
}

int Raylib::Mouse::getX()
{
    return GetMouseX();
}

int Raylib::Mouse::getY()
{
    return GetMouseY();
}

Vector2 Raylib::Mouse::getPosition()
{
    return GetMousePosition();
}

void Raylib::Mouse::setPosition(int x, int y)
{
    SetMousePosition(x, y);
}

void Raylib::Mouse::setOffset(int offsetX, int offsetY)
{
    SetMouseOffset(offsetX, offsetY);
}

void Raylib::Mouse::setScale(float scaleX, float scaleY)
{
    SetMouseScale(scaleX, scaleY);
}

float Raylib::Mouse::getWheelMove()
{
    return GetMouseWheelMove();
}

void Raylib::Mouse::setCursor(int cursor)
{
    SetMouseCursor(cursor);
}