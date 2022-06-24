/*
** EPITECH PROJECT, 2022
** Engine.hpp
** File description:
** Header for event class
*/

#pragma once

namespace Engine {
    namespace Utils {
        template <typename... Types> class onClick {
            public:
                // Ctor
                template <typename Function> onClick(const Function &function) {
                    _function = function;
                }

                // Dtor
                ~onClick() = default;

                // Operators
                template <typename... Arguments> void operator()(Arguments... args) const {
                    (*_function)(args...);
                }

            private:
                // Objects
                void (*_function)(Types...);
        };
    }
}