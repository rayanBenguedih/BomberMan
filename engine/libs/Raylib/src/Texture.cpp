/*
** EPITECH PROJECT, 2022
** Texture.cpp
** File description:
** Texture encapsulation
*/

#include "../includes/Texture.hpp"

Raylib::Texture::Texture(const Image &image)
{
    ::Texture2D texture = LoadTextureFromImage(image);

    id = texture.id;
    width = texture.width;
    height = texture.height;
    mipmaps = texture.mipmaps;
    format = texture.format;
}

Raylib::Texture::~Texture()
{
    unload();
}

void Raylib::Texture::unload()
{
    UnloadTexture(*this);
}