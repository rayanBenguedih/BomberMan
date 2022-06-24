/*
** EPITECH PROJECT, 2022
** Engine.hpp
** File description:
** Header for the creation of the engine
*/

#include "../includes/Image.hpp"

Raylib::Image::Image(const std::string &filePath)
{
    ::Image image = LoadImage(filePath.c_str());

    data = image.data;
    width = image.width;
    height = image.height;
    mipmaps = image.mipmaps;
    format = image.format;
}

Raylib::Image::~Image()
{
    unload();
}

void Raylib::Image::unload()
{
    if (data) {
        UnloadImage(*this);
        data = NULL;
    }
}