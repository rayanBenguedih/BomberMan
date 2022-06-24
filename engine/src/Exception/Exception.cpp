/*
** EPITECH PROJECT, 2022
** Exception.cpp
** File description:
** Exception class
*/

#include "../../includes/Exception/Exception.hpp"

Engine::Exception::Exception(const std::string &message, const std::string
&component) : _message(message), _component(component)
{
}

const std::string &Engine::Exception::getComponent() const
{
    return _component;
}


Engine::PlayerSoundException::PlayerSoundException(const std::string
&message, const std::string &component) : Exception(message, component)
{
}