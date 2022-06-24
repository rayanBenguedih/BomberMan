/*
** EPITECH PROJECT, 2022
** collisions.cpp
** File description:
** collisions.cpp
*/

#include "gamecore/includes/core.hpp"
#include "engine/includes/Engine.hpp"
#include "engine/includes/Entities/Player.hpp"
#include "engine/includes/raylib.h"
#include "engine/libs/Raylib/includes/Camera3D.hpp"
#include "engine/libs/Raylib/includes/Collision.hpp"
#include "engine/libs/Raylib/includes/Keyboard.hpp"
#include "engine/libs/Raylib/includes/Raylib.hpp"

bool collision(Core *core,std::vector<Vector3> wallsPos, int _index, std::vector<Vector3> boxesPos,
               std::vector<Vector3> bombsPos, Entities::Player player,
               float x, float z, bool troughWall, std::string str)
{
    float x_modif = 0;
    float y_modif = 0;

    if (str == "LEFT") {
        x_modif = -1;
    } else if (str == "RIGHT") {
        x_modif = 1;
    } else if (str == "DOWN") {
        y_modif = 1;
    } else if (str == "UP")
        y_modif = -1;
    std::vector<float> data = core->_players[_index]._coord;
    
    if ((data[0] + x_modif) <= 0 || (data[1] + y_modif) <= 0 || (data[0] + x_modif) >= core->_map.size() || (data[1] + y_modif) >= core->_map[0].size())
        return (true);
    
    x_modif *= core->_players[_index]._speed;
    y_modif *= core->_players[_index]._speed;
    // 0.04 = 4
    int l_a = static_cast<int>(core->_players[_index]._coord[0] * 100);
    int l_b = static_cast<int>(core->_players[_index]._coord[1] * 100);
    int speed_x = static_cast<int>(x_modif * 100);
    int speed_y = static_cast<int>(y_modif * 100);
    l_a += speed_x;
    l_b += speed_y;
    int x_rest = l_a%100;
    int y_rest = l_b%100;
    l_a -= l_a%100;
    l_b -= l_b%100;
    l_a = l_a/100;
    l_b = l_b/100;

    if (x_rest >= 50)
        l_a += 1;
    if (y_rest >= 50)
        l_b += 1;
    int tmp = l_a;
    l_a = l_b;
    l_b = tmp;
    if (core->_map[l_a][l_b] == '#' || core->_map[l_a][l_b] == 'M')
        return (true);
    return false;
}
