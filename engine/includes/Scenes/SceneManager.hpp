/*
** EPITECH PROJECT, 2022
** SceneManager.hpp
** File description:
** Header of scene manager
*/

#pragma once

#include "IScene.hpp"
#include <iostream>
#include <memory>
#include <map>

namespace Engine {
    class SceneManager {
        public:
            static SceneManager* getInstance(void);

            // Dtor
            ~SceneManager();

            // Member functions
            std::shared_ptr<IScene> getCurrentScene(void);
            void add(std::shared_ptr<IScene> scene);
            void load(unsigned int sceneId);
            void remove(unsigned int sceneId);

        private:
            // Ctor
            SceneManager();

            // Objects
            static SceneManager* _instance;
            std::map<unsigned int, std::shared_ptr<IScene>> _sceneList;
            std::pair<unsigned int, std::shared_ptr<IScene>> _currentScene;
    };
}

