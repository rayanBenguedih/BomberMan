/*
** EPITECH PROJECT, 2022
** Objects.hpp
** File description:
** Objects interface
*/

#ifndef OBJECTS
#define OBJECTS

#include <string>
#include <vector>

namespace Objects {
    class Objects {
        protected:
            std::size_t _stack = 1;
            std::size_t _availiable = 1;
        public:
            virtual ~Objects(void) = default;

            std::size_t getStack() const;
            std::size_t getAvaliable(void) const;

            virtual void setStack(std::size_t);
            virtual void setAvaliable(int);
    };
}

#endif
