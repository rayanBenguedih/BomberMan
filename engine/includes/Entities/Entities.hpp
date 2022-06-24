
/*
** EPITECH PROJECT, 2022
** Entities.hpp
** File description:
** Entities interface
*/

#ifndef ENTITIES
#define ENTITIES

#include "../../../engine/libs/Raylib/includes/Raylib.hpp"
#include "../../../engine/libs/Raylib/includes/Sound.hpp"
#include "../../../engine/libs/Raylib/includes/Model.hpp"
#include "../../../engine/includes/Exception/Exception.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <memory>

namespace Entities {
    class IEntities {
        public:

            // Dtor
            virtual ~IEntities(){};

            // Member functions
            virtual void setTexture(std::string) = 0;
            virtual void animate(std::string animation, std::size_t animationNb) = 0;
            virtual void setPosition(float x, float y, float z) = 0;
            virtual void setPosition(Vector3) = 0;
            virtual Vector3 getPosition(void) const = 0;
            virtual void playSound(std::string) = 0;
            virtual void draw(void) = 0;
            virtual BoundingBox getSize(void) = 0;
    };
}

#endif
