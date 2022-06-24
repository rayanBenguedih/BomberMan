/*
** EPITECH PROJECT, 2022
** Player.cpp
** File description:
** Player functions
*/

#include "../../includes/Entities/Player.hpp"
#include "../../libs/Raylib/includes/raymath.h"
#include <iostream>

Entities::Player::Player(Raylib::Model *model,
    std::map<std::string, ModelAnimation> animations,
    std::map<std::string, void *(*)(Entities::Player *)> functions,
    std::map<std::string, Objects::Objects *> objects,
    std::map<std::string, std::shared_ptr<Raylib::Sound>> sounds,
    float direction) :
    _animations(animations),
    _functions(functions),
    _sounds(sounds),
    _objects(objects),
    _model(model),
    _direction(direction)
{
    _model->transform = MatrixRotateXYZ({DEG2RAD * 0, DEG2RAD, DEG2RAD * 90});
    _rotationAxis = {1.0f, 0.0f, 0.0f};
    _direction = -90.0f;
    _size = this->_model->getBoundingBox().max;
}

//-----------------------------Getter------------------------------------------
Vector3 Entities::Player::getPosition(void) const
{
    return (this->_position);
}

float Entities::Player::getSpeed(void) const
{
    return (this->_speed);
}

Vector3 Entities::Player::getSizeMax(void)
{
    return (this->_size);
}

BoundingBox Entities::Player::getSize(void)
{
    return (this->_model->getBoundingBox());
}

int Entities::Player::getBomb(void) const
{
    return _currentBomb;
}

Objects::Objects *Entities::Player::getObject(std::string objName)
{
    return (this->_objects[objName]);
}

//--------------------------Setter---------------------------------------------

void Entities::Player::setTexture(std::string)
{
    //unused
}

void Entities::Player::setPosition(float x, float y, float z)
{
    this->_position.x = x;
    this->_position.y = y;
    this->_position.z = z;
}

void Entities::Player::setPosition(Vector3 newPos)
{
    this->_position = newPos;
}

void Entities::Player::setSpeed(float speed)
{
    this->_speed = speed;
}

void Entities::Player::addingBomb(void)
{
    _currentBomb++;
}

void Entities::Player::removeBomb(void)
{
    _currentBomb--;
}

//--------------------------−Functions-----------------------------------------

void Entities::Player::moveUp(void)
{
    _rotationAxis = {0.0f, 1.0f, 1.0f};
    _direction = 180.0f;
    _model->transform = MatrixRotateXYZ({DEG2RAD, DEG2RAD, DEG2RAD});
    this->_position.z -= 2.0f * this->_speed;
}

void Entities::Player::moveDown(void)
{
    _rotationAxis = {1.0f, 0.0f, 0.0f};
    _direction = -90.0f;
    _model->transform = MatrixRotateXYZ({DEG2RAD, DEG2RAD, DEG2RAD});
    this->_position.z += 2.0f * this->_speed;
}

void Entities::Player::mouveLeft(void)
{
    _rotationAxis = {1.0f, 0.0f, 0.0f};
    _direction = -90.0f;
    _model->transform = MatrixRotateXYZ({DEG2RAD, DEG2RAD, DEG2RAD * 90});
    this->_position.x -= 2.0f * this->_speed;
}

void Entities::Player::moveRight(void)
{
    _rotationAxis = {0.0f, 1.0f, 1.0f};
    _direction = 180.0f;
    _model->transform = MatrixRotateXYZ({DEG2RAD, DEG2RAD, DEG2RAD * 90});
    this->_position.x += 2.0f * this->_speed;
}

void Entities::Player::playSound(std::string sound)
{
    std::map<std::string, std::shared_ptr<Raylib::Sound>>::const_iterator soun;

    try {
        soun = this->_sounds.find(sound);
    } catch (std::exception &e) {
        std::cerr << e.what();
    }

    if (soun != this->_sounds.end()) {
        if (!soun->second->isPlaying()) {
            if (sound.compare("walk") == 0)
                soun->second->setVolume(0.3);
            soun->second->play();
        }
    } else {
        throw Engine::PlayerSoundException("Cannot execute player function "
        + sound, "player");
    }
}

void *Entities::Player::useFunction(std::string function)
{
    std::map<std::string, void *(*)(Entities::Player *)>::const_iterator funct;

    try {
        funct = this->_functions.find(function);
    } catch (std::exception &e) {
        std::cerr << e.what();
    }


    if (funct != this->_functions.end()) {
        return (funct->second(this));
    } else {
        throw Engine::PlayerSoundException("Cannot execute player function "
                                           + function, "player");
    }
    return nullptr;
}

void Entities::Player::animate(std::string animationName, std::size_t)
{
    std::map<std::string, ModelAnimation>::const_iterator animate;
    ModelAnimation modelAnim;

    if (animate != this->_animations.end()) {
        try {
            _animFrameCounter++;
            modelAnim = this->_animations[animationName];
            this->_model->updateAnimation(modelAnim, _animFrameCounter);
            if (_animFrameCounter >= modelAnim.frameCount)
                _animFrameCounter = 0;
        } catch (std::exception &e) {
            std::cerr << e.what(); // TODO: Replace this error by an exception
        }
    }
}

void Entities::Player::draw(void)
{
    Vector3 scale = {1.0f, 1.0f, 1.0f};
    Vector3 pos = {this->_position.x + 0.25f, this->_position.y, this->_position.z + 0.25f};

    _model->draw(pos, _rotationAxis, _direction, scale);
}
