/*
** EPITECH PROJECT, 2022
** Texture.hpp
** File description:
** Header for texture encapsulation
*/

#pragma once

#include "Raylib.hpp"
#include "Image.hpp"

namespace Raylib {
    class Texture : public ::Texture {
        public:
            // Ctor
            Texture(const Image &image);

            // Dtor
            ~Texture();

            // Member functions
            void unload(void);
    };
}

