/*
** EPITECH PROJECT, 2022
** Model.hpp
** File description:
** Header for encapsulation of Model functions
*/

#pragma once

#include "Raylib.hpp"
#include "Texture.hpp"
#include <iostream>

namespace Raylib {
    class Model : public ::Model {
        public:
            // Ctor
            Model(const std::string &filePath, const std::string &texturePath);

            // Member functions
            void unload(void);
            void unloadModelKeepMeshes(void);
            void setMeshMaterial(int meshId, int materialId);
            void updateAnimation(::ModelAnimation &anim, int frame);
            ::BoundingBox getBoundingBox(void);
            Vector3  getSize(void);
            void draw(Vector3 position, Vector3 rotationAxis, float
            rotationAngle, Vector3 scale);

            // Objects
            ::Texture2D _texture;
    };
}
