/*
** EPITECH PROJECT, 2022
** player.hpp
** File description:
** player.hpp
*/

#pragma once

#include <iostream>
#include <chrono>
#include <vector>

class Player {
    public :
        // Ctor
        Player();

        // Dtor
        ~Player() = default;

        // Functions
        void increasePower();
        void increaseBombs();
        void increaseSpeed();
        void canThroughWall();
        void resetPlayer();

        //  Objects
        std::vector<float> _coord;
        int _powerOfBomb;
        int _numberOfBombs;
        int _currentOfBombs;
        int _impossible;
        float _speed;
        bool _throughWalls;
        bool _alive;
};

class Bomb {
    public :
        // Ctor
        Bomb(int player, int power, int x, int y);

        // Dtor
        ~Bomb() = default;

        // Functions
        void passLap();

        //  Objects
        int _player;
        std::chrono::time_point<std::chrono::high_resolution_clock> _start;
        int _power;
        int _x;
        int _y;
};
