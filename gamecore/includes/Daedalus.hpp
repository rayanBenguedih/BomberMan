/*
** EPITECH PROJECT, 2022
** B-YEP-400-LIL-4-1-indiestudio-pierre-jean.descarpentries
** File description:
** bot
*/

#pragma once

#include "core.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
#include "math.h"
#include <array>
#include <chrono>
#include <cstring>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <list>
#include <limits>
#include <algorithm>

typedef std::pair<int, int> Pair;
typedef std::tuple<double, int, int> Tuple;

size_t **array_generator(size_t width, size_t height, std::vector<std::string> map);
std::vector<std::string> aStarSearch(size_t **grid, const Pair& src, const Pair& dest, size_t ROW, size_t COL);

namespace Daedalus {
    struct cell
    {
        Pair parent;
        // pos x, pos y, cost
        double f;
        double g;
        double h;

        cell();
    };

    class aStar
    {

    public:
        class Snode
        {
        public:
            bool obstacle = false;
            bool visited = false;
            float fGlobal; // Global distance
            float fLocal;  // Local distance
            int x;
            int y;
            std::vector<Snode *> neighbors; // vecteur des voisins, pointeurs
            Snode *parent;                  // owner
        };

        Snode *nodesArray = nullptr;

        Snode *nodeStart = nullptr;
        Snode *nodeEnd = nullptr;

        std::vector<std::string> _map;

        int mapWidth = 20;
        int mapHeight = 20;

        void createNode();

        void setObstacles(std::vector<std::string> map, bool pass);

        void createConnections(std::vector<std::string> map, bool pass);

        void setObjectives(int startX, int startY, int endX, int endY);

        float distance(Snode *node1, Snode *node2);

        float heuristic(Snode *node1, Snode *node2);

        void aStarSearch(void);

        std::vector<std::string> getPath(void);
    };

    class Neron
    {
    public:
        std::vector<std::string> _map;
        int _bombsMax;
        std::vector<int> _pos;
        int _searchRadius;
        std::vector<int> _targetPos;
        int action;
        size_t _bombRadius;
        int _impossible;
        std::vector<std::string> _path;
        int _difficulty;
        int _index;
        std::vector<std::vector<int>> _bombPos;
        Core *_core;
        int _fleeing;
        std::ofstream outdata;

        Neron(Core *game, std::vector<float> botPos, int pos);

        int myAbs(int val);

        int in_bomb_radius(void);

        int power_up_reachable(void);

        void get_data(std::vector<std::string> myMap, std::vector<float> newPos);

        std::vector<std::string> find_path(std::vector<int> start, std::vector<int> end);

        Pair find_proximity(char tar, std::vector<int> pos, int radius);

        int place_bomb(void);

        int fetch_power_up(void);

        int player_unreachable(void);

        int noBombsMines(void);

        int start_searching(void);

        size_t find_bomb_rad(int x, int y);

        void carpet_bomb_map(void);

        int flee_bomb(void);

        int look_nearest_player(void);

        void protocolThreeProtectCoder(void);

        void run_algorithm(void);

        void break_wall(void);

        int play_game(void);

        void set_difficulty(int difficulty);
    };

}