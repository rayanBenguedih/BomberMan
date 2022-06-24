/*
** EPITECH PROJECT, 2022
** Material.cpp
** File description:
** Material functions encapsulation
*/

#include "../includes/Material.hpp"

Raylib::Material::Material()
{
    ::Material material = LoadMaterialDefault();

    shader = material.shader;
    maps = material.maps;
    params[0] = material.params[0];
    params[1] = material.params[1];
    params[2] = material.params[2];
    params[3] = material.params[3];
}

Raylib::Material::~Material()
{
    unload();
}

void Raylib::Material::unload()
{
    if (maps) {
        UnloadMaterial(*this);
        maps = nullptr;
    }
}

void Raylib::Material::setTexture(int mapType, Texture2D &texture)
{
    SetMaterialTexture(this, mapType, texture);
}
