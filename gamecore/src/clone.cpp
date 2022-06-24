/*
** EPITECH PROJECT, 2022
** clone.cpp
** File description:
** clone.cpp
*/

#include "../includes/Daedalus.hpp"

std::vector<std::string> map_generator(size_t width, size_t height)
{
    // generate a map with # as borders and . as empty space with players amount of P characters randomly
    std::vector<std::string> map;
    std::string line;

    srand(time(NULL));

    for (size_t i = 0; i < height; i++) {
        line = "";
        for (size_t j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1 || rand()%10 <= 3)
                line += "#";
            else if (rand()%10 <= 4)
                line += "M";
            else
                line += ".";
        }
        map.push_back(line);
    }

    for (int lif = 0; lif <= rand()%5+3; lif++) {

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            int count = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (i + k < height && j + l < width && map[i + k][j + l] == '#')
                        count++;
                }
            }
            if (map[i][j] == '#')
                count--;
            if (count < 2 || count > 2) {
                if (rand() % 10 <= 3) // change to more boxes
                    map[i][j] = 'M';
                else
                    map[i][j] = '.';
            } else if (count == 2)
                map[i][j] = '#';
        }
    }
    }

    // find a cross shaped place and put a P in it

    // add walls to extremeities of map
    for (size_t i = 0; i < height; i++) {
        map[i][0] = '#';
        map[i][width - 1] = '#';
    }
    for (size_t i = 0; i < width; i++) {
        map[0][i] = '#';
        map[height - 1][i] = '#';
    }

    map[1][1] = 'V';
    map[1][2] = '.';
    map[2][1] = '.';
    map[1][width - 2] = 'V';
    map[2][width - 2] = '.';
    map[1][width - 3] = '.';
    map[height - 2][1] = 'V';
    map[height - 2][2] = '.';
    map[height - 3][1] = '.';
    map[height - 2][width - 2] = 'V';
    map[height - 3][width - 2] = '.';
    map[height - 2][width - 3] = '.';

    // randomly replaces # with M
    for (size_t i = 1; i < height-1; i++) {
        for (size_t j = 1; j < width-1; j++) {
            if (map[i][j] == '#') {
                if (rand()%10 <= 4)
                    map[i][j] = 'M';
            }
        }
    }
    return (map);
}
