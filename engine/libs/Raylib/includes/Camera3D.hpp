/*
** EPITECH PROJECT, 2022
** Camera3D.hpp
** File description:
** Header for encapsulation of camera3D functions
*/

#pragma once

#include "Raylib.hpp"

namespace Raylib {
    class Camera3D : public ::Camera3D {
        public:
            // Ctor
            Camera3D(Vector3 position, Vector3 target, Vector3 up, float
            fovy, int projection);

            // Dtor
            ~Camera3D();

            // Member functions
            void beginMode(void);
            void endMode(void);
            void setMode(int mode);
            void setAltControl(int alt);
            void setSmoothZoomControl(int smoothZoom);
            void setMoveControls(int front, int back, int right, int left, int up, int down);
            void update(void);
    };
}