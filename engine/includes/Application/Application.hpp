/*
** EPITECH PROJECT, 2022
** Application.hpp
** File description:
** Header for the creation of the application into game engine
*/

#pragma once

#include "../../libs/Raylib/includes/Window.hpp"
#include "../../libs/Raylib/includes/Mouse.hpp"
#include "../../libs/Raylib/includes/Keyboard.hpp"
#include "../../libs/Raylib/includes/Gamepad.hpp"
#include "../../includes/Scenes/SceneManager.hpp"
#include <memory>

namespace Engine {
    class Application {
        public:
            // Ctor
            Application(unsigned int width, unsigned int height, const
            std::string &titleWindow, int gamepadId);

            // Dtor
            ~Application();

            // Member functions
            void run(void);
            void update(void);

            // Getters
            SceneManager *getSceneManager(void);

        private:
            // Objects
            std::unique_ptr<Raylib::Window> _window;
            std::unique_ptr<Raylib::Keyboard> _keyboard;
            std::unique_ptr<Raylib::Mouse> _mouse;
            std::unique_ptr<Raylib::Gamepad> _gamepad;
            SceneManager* _sceneManager;
    };
}