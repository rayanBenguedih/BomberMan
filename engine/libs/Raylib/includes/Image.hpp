/*
** EPITECH PROJECT, 2022
** Image.hpp
** File description:
** Header for Iamge encapsulation
*/

#pragma once

#include "Raylib.hpp"
#include <string>

namespace Raylib {
    class Image : public ::Image {
        public:
            // Ctor
            Image(const std::string &filePath);

            // Dtor
            ~Image();

            // Member functions
            void unload(void);
    };
}