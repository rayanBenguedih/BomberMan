/*
** EPITECH PROJECT, 2022
** Button.cpp
** File description:
** Button component
*/

#include "../../includes/Components/Button.hpp"

Engine::Components::Button::Button(const std::string &soundPath, const
std::string &texturePath, Utils::onClick<> onClick, int x, int y) :
_soundPressed(Raylib::Sound(soundPath)),
_button(Raylib::Texture(Raylib::Image(texturePath))),
_frameHeight(static_cast<float>(_button.height) / 3),
_onClick(onClick),
_source(Raylib::Rectangle(0, 0,_button.width, _frameHeight, Raylib::Color(0,0,0,255))),
_bounds(Raylib::Rectangle(x, y,static_cast<float>(_button.width),_frameHeight, Raylib::Color(0, 0, 0, 255)))
{
    _state = NORMAL;
    _isPressed = false;
}

Engine::Components::Button::~Button()
{
    _button.unload();
    _soundPressed.unload();
}

void Engine::Components::Button::display()
{
    ::DrawTextureRec(_button, _source, (Vector2){_bounds.x, _bounds.y}, WHITE);
}

void Engine::Components::Button::checkEvent(Raylib::Mouse *mouse)
{
    _isPressed = false;
    if (::CheckCollisionPointRec(mouse->getPosition(), _bounds)) {
        if (mouse->isButtonDown(MOUSE_BUTTON_LEFT))
            _state = PRESSED;
        else
            _state = HOVER;

        if (mouse->isButtonReleased(MOUSE_BUTTON_LEFT))
            _isPressed = true;
    } else {
        _state = NORMAL;
    }

    if (_isPressed) {
        _soundPressed.play();
        _onClick();
    }

    _source.y = _state * _frameHeight;
}