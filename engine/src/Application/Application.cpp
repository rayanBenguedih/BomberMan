/*
** EPITECH PROJECT, 2022
** Application.cpp
** File description:
** Creation of the application into engine
*/

#include "../../includes/Application/Application.hpp"

Engine::Application::Application(unsigned int width, unsigned int height,
                                 const std::string &titleWindow, int gamepadId)
{
    _window = std::make_unique<Raylib::Window>(width, height, titleWindow);
    _keyboard = std::make_unique<Raylib::Keyboard>();
    _mouse = std::make_unique<Raylib::Mouse>();
    _gamepad = std::make_unique<Raylib::Gamepad>(gamepadId);
    _sceneManager = Engine::SceneManager::getInstance();
}

Engine::Application::~Application()
{
    _window->close();
}

void Engine::Application::run()
{
    _window->setMaxFPS(60);
    while (!_window->shouldClose()) {
        if (_keyboard->isKeyDown(32)) {
            _sceneManager->load(2);
        }
        update();
    }
}

void Engine::Application::update()
{
    _window->beginDraw();
    _window->clearBackground(Raylib::Color(255, 255, 255, 255));
    _sceneManager->getCurrentScene()->update();
    _window->endDraw();
}

Engine::SceneManager *Engine::Application::getSceneManager()
{
    return _sceneManager;
}