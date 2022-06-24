/*
** EPITECH PROJECT, 2022
** Camera3D.cpp
** File description:
** Camera3D functions encapsulation
*/


#include "../includes/Camera3D.hpp"

Raylib::Camera3D::Camera3D(Vector3 positionValue, Vector3 targetValue, Vector3
upValue, float fovyValue, int projectionValue)
{
    position = positionValue;
    target = targetValue;
    up = upValue;
    fovy = fovyValue;
    projection = projectionValue;
}

Raylib::Camera3D::~Camera3D() = default;

void Raylib::Camera3D::beginMode()
{
    BeginMode3D(*this);
}

void Raylib::Camera3D::endMode()
{
    EndMode3D();
}

void Raylib::Camera3D::setMode(int mode)
{
    SetCameraMode(*this, mode);
}

void Raylib::Camera3D::setAltControl(int alt)
{
    SetCameraAltControl(alt);
}

void Raylib::Camera3D::setSmoothZoomControl(int smoothZoom)
{
    SetCameraSmoothZoomControl(smoothZoom);
}

void Raylib::Camera3D::setMoveControls(int front, int back, int right, int left, int up, int down)
{
    SetCameraMoveControls(front, back, right, left, up, down);
}

void Raylib::Camera3D::update()
{
    UpdateCamera(this);
}