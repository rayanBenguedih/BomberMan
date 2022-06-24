/*
** EPITECH PROJECT, 2022
** Engine.cpp
** File description:
** Creation of the engine
*/

#include "../includes/Engine.hpp"

Engine::Engine* Engine::Engine::_instance(nullptr);

Engine::Engine* Engine::Engine::getInstance()
{
    if (_instance == nullptr)
        _instance = new Engine();
    return _instance;
}

Engine::Engine::Engine()
{
    _application = nullptr;
}

Engine::Engine::~Engine()
{
    delete _instance;
    _instance = nullptr;
}

void Engine::Engine::createApp(unsigned int width, unsigned int height, const
std::string &titleWindow, int gamepadId)
{
    _application = std::make_unique<Application>(width, height, titleWindow, gamepadId);
}