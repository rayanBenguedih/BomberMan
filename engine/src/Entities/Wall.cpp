/*
** EPITECH PROJECT, 2022
** Wall.cpp
** File description:
** Wall functions
*/

#include "../../includes/Entities/Wall.hpp"

Entities::Wall::Wall(Vector3 pos,
    std::shared_ptr<Raylib::Model> model,
    std::map<std::string, ModelAnimation> animations,
    std::shared_ptr<Raylib::Sound> sound,
    bool breakable) :
    _position(pos),
    _model(model),
    _animations(animations),
    _sound(sound),
    _breackable(breakable)
{
    // unused
}

//-------------------------------Setter----------------------------------------
void Entities::Wall::setTexture(std::string)
{
    // unused
}

void Entities::Wall::setPosition(float x, float y, float z)
{
    this->_position.x = x;
    this->_position.y = y;
    this->_position.z = z;
}

void Entities::Wall::setPosition(Vector3 newPos)
{
    this->_position = newPos;
}

//---------------------------------Getter--------------------------------------

Vector3 Entities::Wall::getPosition(void) const
{
    return (this->_position);
}

BoundingBox Entities::Wall::getSize(void)
{
    return (this->_model->getBoundingBox());
}

//------------------------------Functions--------------------------------------

void Entities::Wall::playSound(std::string)
{
    this->_sound->play();
}

void Entities::Wall::animate(std::string animation, std::size_t frame)
{
    std::map<std::string, ModelAnimation>::const_iterator animate;
    ModelAnimation modelAnim;

    try {
        if (this->_loadedAnimation != animation) {
            animate = this->_animations.find(animation);
        }
    } catch (std::exception &e) {
        std::cerr << e.what();
    }

    if (animate != this->_animations.end()) {
        if (this->_loadedAnimation != animation)
        this->_loadedAnimation = animation;
        modelAnim = this->_animations[animation];
        this->_model->updateAnimation(modelAnim, frame);
    }
}

void Entities::Wall::draw(void)
{
    Vector3 rotationAxis = {0.0f, 0.0f, 0.0f};
    Vector3 scale = {0.9, 0.9f, 0.9f};

    _model->draw(this->_position, rotationAxis, 0.0f, scale);
    //std::cout << "je passe par ici" << std::endl;
}
