/*
** EPITECH PROJECT, 2022
** Window.hpp
** File description:
** Header for encapsulation of window functions
*/

#pragma once

#include "Raylib.hpp"
#include "Color.hpp"
#include <string>

namespace Raylib {
    class Window {
        public:
            // Ctor
            Window(unsigned int width, unsigned int height, const std::string
            &title);

            // Member functions
            bool init(unsigned int width, unsigned int height, const
            std::string &title);
            void close(void);
            bool isReady(void);
            bool shouldClose(void) const;
            Window &setState(unsigned int flag);
            Window &clearState(unsigned int flag);
            Window &clearBackground(const Raylib::Color &color);
            Window &toggleFullScreenAndWindowed(void);
            Window &maximize(void);
            Window &minimize(void);
            Window &restore(void);
            Window &setIcon(const Image &image);
            Window &setPositionOnScreen(unsigned int x, unsigned int y);
            Window &setMinimumSize(unsigned int width, unsigned int height);
            Window &setSize(unsigned int width, unsigned int height);
            Window &beginDraw(void);
            Window &endDraw(void);
            int getFPS(void) const;
            Window &drawFPSOnScreen(unsigned int x, unsigned int y);
            Window &setMaxFPS(unsigned int fps);
    };
}
