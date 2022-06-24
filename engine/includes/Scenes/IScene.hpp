/*
** EPITECH PROJECT, 2022
** IScene.hpp
** File description:
** Interface for scene
*/

#pragma once

namespace Engine {
    class IScene {
        public:
            // Ctor
            IScene(){}

            // Dtor
            virtual ~IScene(){}

            // Member functions
            virtual void initialize(void) = 0;
            virtual void update(void) = 0;
            virtual void clear(void) = 0;
    };
}