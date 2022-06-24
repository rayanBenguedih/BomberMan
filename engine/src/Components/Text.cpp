/*
** EPITECH PROJECT, 2022
** Text.cpp
** File description:
** Text component
*/

#include "../../includes/Components/Text.hpp"

Engine::Components::Text::Text(const std::string &text, unsigned int r,
                               unsigned int g, unsigned int b, unsigned int a,
                               int x, int y)
{
    std::unique_ptr<Raylib::Text> str = std::make_unique<Raylib::Text>(text,Raylib::Color(r, g, b, a));
    str->draw(x, y);
}

Engine::Components::Text::~Text() = default;