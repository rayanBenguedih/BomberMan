/*
** EPITECH PROJECT, 2022
** Camera3D.hpp
** File description:
** Header for encapsulation of camera3D functions
*/

#pragma once

#include "Raylib.hpp"

namespace Raylib {
    class Collision {
        public:
            // Ctor
            Collision();

            // Dtor
            ~Collision();

            // Member functions
            bool checkCollisionSpheres(Vector3 center1, float radius1, Vector3
            center2, float radius2);
            bool checkCollisionBoxes(BoundingBox box1, BoundingBox box2);
            bool checkCollisionBoxSphere(BoundingBox box, Vector3 center, float
            radius);
    };
}