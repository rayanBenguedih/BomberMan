/*
** EPITECH PROJECT, 2022
** Model.cpp
** File description:
** Model functions encapsulation
*/

#include "../includes/Model.hpp"
#include "../includes/Texture.hpp"

Raylib::Model::Model(const std::string &filePath, const std::string &texturePath)
{
    ::Model model = LoadModel(filePath.c_str());

    transform = model.transform;
    meshCount = model.meshCount;
    materialCount = model.materialCount;
    meshes = model.meshes;
    materials = model.materials;
    meshMaterial = model.meshMaterial;
    boneCount = model.boneCount;
    bones = model.bones;
    bindPose = model.bindPose;
    _texture = LoadTexture(texturePath.c_str());

    materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
    //::SetMaterialTexture(&materials[0], MATERIAL_MAP_DIFFUSE, _texture);
}

void Raylib::Model::unload()
{
    ::UnloadModel(*this);
}

void Raylib::Model::unloadModelKeepMeshes()
{
    UnloadModelKeepMeshes(*this);
}

void Raylib::Model::setMeshMaterial(int meshId, int materialId)
{
    SetModelMeshMaterial(this, meshId, materialId);
}

void Raylib::Model::updateAnimation(::ModelAnimation &anim, int frame)
{
    UpdateModelAnimation(*this, anim, frame);
}

::BoundingBox Raylib::Model::getBoundingBox()
{
    return GetModelBoundingBox(*this);
}

void Raylib::Model::draw(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale)
{
    DrawModelEx(*this, position, rotationAxis, rotationAngle, scale, WHITE);
}
