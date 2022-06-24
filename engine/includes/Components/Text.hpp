/*
** EPITECH PROJECT, 2022
** Text.hpp
** File description:
** Header for the creation of the text
*/

#pragma once

#include "../../libs/Raylib/includes/Text.hpp"
#include <memory>

namespace Engine {
    namespace Components {
        class Text {
        public:
            // Ctor
            Text(const std::string &text, unsigned int r, unsigned int g,
                 unsigned int b, unsigned int a, int x, int y);

            // Dtor
            ~Text();
        };
    }
}