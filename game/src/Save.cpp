/*
** EPITECH PROJECT, 2022
** save.cpp
** File description:
** Save of the game
*/

#include "../includes/Save.hpp"
#include <iostream>
#include <fstream>

void Bomberman::Save::saveGame(std::vector<std::string> map, std::vector<Entities::Player *> players, std::vector<Entities::Bomb *> bombs)
{
    std::ofstream save;
    std::string informations;
    Vector3 position;
    Objects::Bomb *bomb = nullptr;
    float time = 0;

    save.open("save.txt");
    if (save.bad() == true) {
        std::cerr << "Cannot open the save file" << std::endl;
        return;
    }

    save << "MAP:" << std::endl;
    for (std::string line : map)
        save << line << std::endl;

    save << "PLAYERS:" << std::endl;
    for (Entities::Player *player : players) {
        try {
            bomb = (Objects::Bomb *)player->useFunction("getBomb");
            position = player->getPosition();

            informations = std::to_string(position.x) + " ";
            informations += std::to_string(position.y) + " ";
            informations += std::to_string(position.z) + " ";
            informations += std::to_string(bomb->getRange()) + " ";
            informations += std::to_string(bomb->getStack()) + " ";
            informations += std::to_string(bomb->getAvaliable());

            save << informations << std::endl;
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return;
        }
    }

    save << "CURRENT BOMB:" << std::endl;
    for (Entities::Bomb *bomb : bombs) {
        try {
            position = bomb->getPosition();
            time = bomb->getTiming() - clock();

            informations = std::to_string(position.x) + " ";
            informations += std::to_string(position.y) + " ";
            informations += std::to_string(position.z) + " ";
            informations += std::to_string(bomb->getRange()) + " ";
            informations += std::to_string(time);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return;
        }
    }
    save.close();
}

std::tuple<std::vector<std::string>, std::vector<std::vector<float>>, std::vector<std::vector<float>>> Bomberman::Save::loadSave(void)
{
    std::tuple<std::vector<std::string>, std::vector<std::vector<float>>, std::vector<std::vector<float>>> informations;
    std::vector<std::string> map;
    std::vector<std::vector<float>> players;
    std::vector<std::vector<float>> bombs;
    std::ifstream save("save.txt");
    std::string line = nullptr;

    if (save.bad() == true) {
        std::cerr << "Error wile opening the save" << std::endl;
        return (informations);
    }
    save >> line;

    if (line != "MAP:") {
        std::cerr << "Corrupted file";
        return (informations);
    }
    while (save.eof() == false && line != "PLAYERS:") {
        save >> line;
        map.push_back(line);
    }


    for (int playerInfo = 0; playerInfo < 4; playerInfo++) {
        save >> line;
        for (int i = 0; i < 6; i++) {
            players[playerInfo].push_back(std::stof(line.substr(0, line.find(" "))));
            if (i < 5)
                line.erase(0, line.find(" ") + 1);
        }
    }
    if (line != "CURRENT BOMB:") {
        std::cerr << "Corrupted file";
        return (informations);
    }


    for (int bombInfo = 0; save.eof() == false; bombInfo++) {
        save >> line;
        for (int i = 0; i < 5; i++) {
            bombs[bombInfo].push_back(std::stof(line.substr(0, line.find(" "))));
            if (i < 4)
                line.erase(0, line.find(" ") + 1);
        }
    }

    std::get<0>(informations) = map;
    std::get<1>(informations) = players;
    std::get<2>(informations) = bombs;
    return (informations);
}
