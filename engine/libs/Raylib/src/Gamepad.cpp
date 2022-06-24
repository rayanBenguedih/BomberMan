/*
** EPITECH PROJECT, 2022
** Gamepad.cpp
** File description:
** Header for encapsulation of gamepad functions
*/

#include "../includes/Gamepad.hpp"

Raylib::Gamepad::Gamepad(int gamepad) : _gamepad(gamepad)
{
}

Raylib::Gamepad::~Gamepad() = default;

bool Raylib::Gamepad::isAvailable()
{
    return IsGamepadAvailable(_gamepad);
}

std::string Raylib::Gamepad::getName()
{
    std::string s(GetGamepadName(_gamepad));
    return s;
}

bool Raylib::Gamepad::isButtonPressed(int button)
{
    return IsGamepadButtonPressed(_gamepad, button);
}

bool Raylib::Gamepad::isButtonDown(int button)
{
    return IsGamepadButtonDown(_gamepad, button);
}

bool Raylib::Gamepad::isButtonReleased(int button)
{
    return IsGamepadButtonReleased(_gamepad, button);
}

bool Raylib::Gamepad::isButtonUp(int button)
{
    return IsGamepadButtonUp(_gamepad, button);
}

int Raylib::Gamepad::getButtonPressed()
{
    return GetGamepadButtonPressed();
}

int Raylib::Gamepad::getAxisCount()
{
    return GetGamepadAxisCount(_gamepad);
}

float Raylib::Gamepad::getAxisMovement(int axis)
{
    return GetGamepadAxisMovement(_gamepad, axis);
}

int Raylib::Gamepad::setMappings(const char *mappings)
{
    return SetGamepadMappings(mappings);
}