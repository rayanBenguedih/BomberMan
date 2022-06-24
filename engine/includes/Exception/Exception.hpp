/*
** EPITECH PROJECT, 2022
** Exception.hpp
** File description:
** Exception class
*/

#ifndef EXCEPTION
#define EXCEPTION

#include <iostream>
#include <exception>

namespace Engine {
    class Exception : public std::exception {
        public:
            // Ctor
            explicit Exception(const std::string &message, const std::string
            &component = "Unknown");

            // Dtor
            virtual ~Exception(void) = default;

            // Member functions
            virtual const std::string &getComponent() const;

        private:
            // Objects
            std::string _message;
            std::string _component;
    };

    class PlayerSoundException : public Exception {
        public:
            // Ctor
            PlayerSoundException(const std::string &message, const
            std::string &component = "Unknown");
    };
}

#endif
