/*
** EPITECH PROJECT, 2022
** Bomb.cpp
** File description:
** Bomb functions
*/

#include "../../includes/Entities/Bomb.hpp"

//---------------------------------Object--------------------------------------
    //-----------------------------Getter--------------------------------------

std::size_t Objects::Bomb::getRange(void) const
{
    return (this->_range);
}
    //------------------------------Setter-------------------------------------
void Objects::Bomb::setRange(int range)
{
    this->_range += range;
}

void Objects::Bomb::setStack(int stack)
{
    this->_stack += stack;
}

void Objects::Bomb::setAvaliable(int bombs)
{
    if (this->_availiable < this->_stack)
        this->_availiable += bombs;
}

//-----------------------------End of Objects----------------------------------


//-------------------------------Entities--------------------------------------

Entities::Bomb::Bomb(Vector3 pos,
    std::shared_ptr<Raylib::Model> model,
    std::map<std::string, ModelAnimation> animations,
    std::shared_ptr<Raylib::Sound> sound) :
    _position(pos),
    _model(model),
    _animations(animations),
    _sound(sound)
{
    this->_start = clock();
}

//-------------------------------Setter----------------------------------------
void Entities::Bomb::setPosition(float x, float y, float z)
{
    this->_position.x = x;
    this->_position.y = y;
    this->_position.z = z;
}

void Entities::Bomb::setPosition(Vector3 newPos)
{
    this->_position = newPos;
}

void Entities::Bomb::setRange(int toAdd)
{
    this->_bomb.setRange(toAdd);
}

void Entities::Bomb::setStack(int toAdd)
{
    this->_bomb.setStack(toAdd);
}

void Entities::Bomb::setAvaliable(int toAdd)
{
    this->_bomb.setAvaliable(toAdd);
}

//---------------------------------Getter--------------------------------------

Vector3 Entities::Bomb::getPosition(void) const
{
    return (this->_position);
}

BoundingBox Entities::Bomb::getSize(void)
{
    return (this->_model->getBoundingBox());
}

std::size_t Entities::Bomb::getStack(void) const
{
    return (this->_bomb.getStack());
}

std::size_t Entities::Bomb::getRange(void) const
{
    return (this->_bomb.getRange());
}

std::size_t Entities::Bomb::getAvaliable(void) const
{
    return (this->_bomb.getAvaliable());
}

clock_t Entities::Bomb::getTiming(void) const
{
    return (this->_start);
}

//------------------------------Functions--------------------------------------

void Entities::Bomb::playSound(std::string)
{
    this->_sound->play();
}

void Entities::Bomb::animate(std::string animation, int frame)
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

void Entities::Bomb::draw(void)
{
    Vector3 rotationAxis = {0.0f, 0.0f, 0.0f};
    Vector3 scale = {5.0f, 5.0f, 5.0f};

    this->_model->draw(this->_position, rotationAxis, 0.0f, scale);
}

void Entities::Bomb::setTexture(std::string)
{
    // unused
}
void Entities::Bomb::animate(std::string, std::size_t)
{
    // unused
}


//----------------------------End of Entities----------------------------------
