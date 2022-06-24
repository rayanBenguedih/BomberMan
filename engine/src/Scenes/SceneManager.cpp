/*
** EPITECH PROJECT, 2022
** SceneManager.cpp
** File description:
** Scene manager
*/

#include "../../includes/Scenes/SceneManager.hpp"
#include <unordered_map>

Engine::SceneManager* Engine::SceneManager::_instance(nullptr);

Engine::SceneManager* Engine::SceneManager::getInstance()
{
    if (_instance == nullptr)
        _instance = new SceneManager;
    return _instance;
}

Engine::SceneManager::SceneManager()
{

}

Engine::SceneManager::~SceneManager()
{
}

std::shared_ptr<Engine::IScene> Engine::SceneManager::getCurrentScene()
{
    return _currentScene.second;
}

void Engine::SceneManager::add(std::shared_ptr<Engine::IScene> scene)
{
    _sceneList.insert(std::make_pair(_sceneList.end()->first + 1, scene));
}

void Engine::SceneManager::load(unsigned int sceneId)
{
    auto sceneIterator = _sceneList.find(sceneId);

    if (sceneIterator != _sceneList.end()) {
        //getCurrentScene()->clear();
        sceneIterator->second->initialize();
        _currentScene = std::pair<unsigned int, std::shared_ptr<IScene>>(sceneIterator->first, sceneIterator->second);
    } else {
        std::cerr << "Error: Scene not found" << std::endl; // TODO: Change the actual error message by an Exception()
    }
}

void Engine::SceneManager::remove(unsigned int sceneId)
{
    auto sceneIterator = _sceneList.find(sceneId);

    if (sceneIterator != _sceneList.end()) {
        if (sceneIterator->second == getCurrentScene())
            std::cerr << "Error: You cannot remove the current scene on the list" << std::endl;
        _sceneList.erase(sceneIterator);
    } else {
        std::cerr << "Error: Scene not found" << std::endl;
    }
}