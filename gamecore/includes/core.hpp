/*
** EPITECH PROJECT, 2022
** core.hpp
** File description:
** core.hpp
*/

#pragma once

#include "player.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include <chrono>

class Core {
    public :
        // Ctor
        Core(int nbPlayers);

        // Dtor
        ~Core() = default;

        // Functions
        void loadMap(char *path);
        float inputInterpretation(const char *input, int player);
        void getLoop();

        //  Objects
        int _nbPlayers;
        std::vector<std::string> _map;
        int _xMax;
        int _yMax;
        std::vector<Bomb> _currentBomb;
        std::vector<std::string> inputs;
        std::vector<bool> jobs;
        std::vector<Player> _players;

    private:
        // Functions
        int placeBomb(Player *player, int who);
        float movePlayer(float x, float y, Player *player, int pos);
        int checkBombRange(int x, int y);
        void checkBomb();
};

