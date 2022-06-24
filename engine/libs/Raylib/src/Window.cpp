/*
** EPITECH PROJECT, 2022
** Window.hpp
** File description:
** Encapsulation of window functions
*/

#include "../includes/Window.hpp"
//#includes "../includes/Exception.hpp"

Raylib::Window::Window(unsigned int width, unsigned int height, const
std::string &title)
{
    init(width, height, title);
    /* if (!init(width, height, title)) {
        throw Exception((std::string &) "Failed to create the window!");
    } */
}

bool Raylib::Window::init(unsigned int width, unsigned int height, const
std::string &title)
{
    InitWindow(width, height, title.c_str());
    return isReady();
}

void Raylib::Window::close()
{
    CloseWindow();
}

bool Raylib::Window::isReady()
{
    return IsWindowReady();
}

bool Raylib::Window::shouldClose() const
{
    return WindowShouldClose();
}

Raylib::Window &Raylib::Window::setState(unsigned int flag)
{
    SetWindowState(flag);
    return *this;
}

Raylib::Window &Raylib::Window::clearState(unsigned int flag)
{
    ClearWindowState(flag);
    return *this;
}

Raylib::Window &Raylib::Window::clearBackground(const Color &color)
{
    ClearBackground(color);
    return *this;
}

Raylib::Window &Raylib::Window::toggleFullScreenAndWindowed()
{
    ToggleFullscreen();
    return *this;
}

Raylib::Window &Raylib::Window::maximize()
{
    MaximizeWindow();
    return *this;
}

Raylib::Window &Raylib::Window::minimize()
{
    MinimizeWindow();
    return *this;
}

Raylib::Window &Raylib::Window::restore()
{
    RestoreWindow();
    return *this;
}

Raylib::Window &Raylib::Window::setIcon(const Image &image)
{
    SetWindowIcon(image);
    return *this;
}

Raylib::Window &Raylib::Window::setPositionOnScreen(unsigned int x, unsigned
int y)
{
    SetWindowPosition(x, y);
    return *this;
}

Raylib::Window &Raylib::Window::setMinimumSize(unsigned int width, unsigned
int height)
{
    SetWindowMinSize(width, height);
    return *this;
}

Raylib::Window &Raylib::Window::setSize(unsigned int width, unsigned int height)
{
    SetWindowSize(width, height);
    return *this;
}

Raylib::Window &Raylib::Window::beginDraw()
{
    BeginDrawing();
    return *this;
}

Raylib::Window &Raylib::Window::endDraw()
{
    EndDrawing();
    return *this;
}

int Raylib::Window::getFPS() const
{
    return GetFPS();
}

Raylib::Window &Raylib::Window::drawFPSOnScreen(unsigned int x, unsigned int y)
{
    DrawFPS(x, y);
    return *this;
}

Raylib::Window &Raylib::Window::setMaxFPS(unsigned int fps)
{
    SetTargetFPS(fps);
    return *this;
}
