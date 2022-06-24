/*
** EPITECH PROJECT, 2022
** Text.hpp
** File description:
** Header for encapsulation of text functions
*/

#pragma once

#include "Raylib.hpp"
#include "Color.hpp"
#include <string>

namespace Raylib {
    class Text {
        public:
            // Ctor
            Text(std::string str, const Color &color);

            // Dtor
            ~Text();

            // Getter and Setter
            const std::string &getStr(void) const;
            void setStr(const std::string &str);
            Color getColor(void) const;
            void setColor(Color &color);
            unsigned int getSize(void) const;
            void setSize(int size);

            // Member functions
            void draw(int x, int y);

        private:
            std::string _str;
            Color _color;
            int _size;
    };
}
