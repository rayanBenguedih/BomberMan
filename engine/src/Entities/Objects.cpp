/*
** EPITECH PROJECT, 2022
** Save.cpp
** File description:
** Save functions
*/

#include "../../includes/Entities/Objects.hpp"

//---------------------------------Object--------------------------------------
    //-----------------------------Getter--------------------------------------

std::size_t Objects::Objects::getStack(void) const
{
    return (this->_stack);
}

std::size_t Objects::Objects::getAvaliable(void) const
{
    return (this->_availiable);
}
    //------------------------------Setter-------------------------------------

void Objects::Objects::setStack(std::size_t stack)
{
    this->_stack += stack;
}

void Objects::Objects::setAvaliable(int availiable)
{
    if (this->_availiable < this->_stack)
        this->_availiable += availiable;
}

//-----------------------------End of Objects----------------------------------
