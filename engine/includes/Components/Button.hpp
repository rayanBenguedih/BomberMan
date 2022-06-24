/*
** EPITECH PROJECT, 2022
** Engine.hpp
** File description:
** Header for the creation of the engine
*/

#pragma once

#include "../../libs/Raylib/includes/Sound.hpp"
#include "../../libs/Raylib/includes/Rectangle.hpp"
#include "../../libs/Raylib/includes/Mouse.hpp"
#include "../../libs/Raylib/includes/Texture.hpp"
#include "../Utils/onClick.hpp"

namespace Engine {
    namespace Components {

        enum buttonStates {
            NORMAL = 0,
            HOVER,
            PRESSED
        };

        class Button {
            public:
                // Ctor
                explicit Button(const std::string &soundPath, const std::string
                &texturePath, Utils::onClick<> onClick, int x, int y);

                // Dtor
                ~Button();

                // Member functions
                void display(void);
                void checkEvent(Raylib::Mouse*);

            private:
                // Objects
                Raylib::Sound _soundPressed;
                Raylib::Texture _button;
                float _frameHeight;
                Raylib::Rectangle _source;
                Raylib::Rectangle _bounds;
                buttonStates _state;
                bool _isPressed;
                Utils::onClick<> _onClick;
        };
    }
}