/*
** EPITECH PROJECT, 2022
** save.cpp
** File description:
** Save of the game
*/

#ifndef SAVE
#define SAVE

#include "../../engine/includes/Entities/Player.hpp"
#include "../../engine/includes/Entities/Bomb.hpp"
#include <vector>
#include <string>
#include <tuple>

namespace Bomberman {
    class Save {
    public:
        static void saveGame(std::vector<std::string>, std::vector<Entities::Player *>, std::vector<Entities::Bomb *>);
        static std::tuple<std::vector<std::string>, std::vector<std::vector<float>>, std::vector<std::vector<float>>> loadSave(void);
    };
}

#endif
