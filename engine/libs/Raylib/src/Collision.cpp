/*
** EPITECH PROJECT, 2022
** Collision.cpp
** File description:
** Collision functions encapsulation
*/

#include "../includes/Collision.hpp"

Raylib::Collision::Collision()
{
}

Raylib::Collision::~Collision()
{
}

bool Raylib::Collision::checkCollisionSpheres(Vector3 center1, float radius1, Vector3 center2, float radius2)
{
    return CheckCollisionSpheres(center1, radius1, center2, radius2);
}

bool Raylib::Collision::checkCollisionBoxes(BoundingBox box1, BoundingBox box2)
{
    return CheckCollisionBoxes(box1, box2);
}

bool Raylib::Collision::checkCollisionBoxSphere(BoundingBox box, Vector3 center, float radius)
{
    return CheckCollisionBoxSphere(box, center, radius);
}