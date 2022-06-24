/*
** EPITECH PROJECT, 2022
** Material.hpp
** File description:
** Header for encapsulation of Material functions
*/

#pragma once

#include "Raylib.hpp"
#include <iostream>
#include <vector>

namespace Raylib {
    class Material : public ::Material {
        public:
            // Ctor
            Material();

            // Dtor
            ~Material();

            // Member functions
            //std::vector<Material> load(const std::string &filePath);
            void unload(void);
            void setTexture(int mapType, Texture2D &texture);
    };
}