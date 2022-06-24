/*
** EPITECH PROJECT, 2022
** Text.hpp
** File description:
** Header for encapsulation of keyboard functions
*/

#include "../includes/Keyboard.hpp"

Raylib::Keyboard::Keyboard()
{
}

Raylib::Keyboard::~Keyboard() = default;

int Raylib::Keyboard::getKeyPressed()
{
    return GetKeyPressed();
}

int Raylib::Keyboard::getCharPressed()
{
    return GetCharPressed();
}

bool Raylib::Keyboard::isKeyPressed(int key)
{
    return IsKeyPressed(key);
}

bool Raylib::Keyboard::isKeyDown(int key)
{
    return IsKeyDown(key);
}

bool Raylib::Keyboard::isKeyReleased(int key)
{
    return IsKeyReleased(key);
}

bool Raylib::Keyboard::isKeyUp(int key)
{
    return IsKeyUp(key);
}