/*
** EPITECH PROJECT, 2022
** player.cpp
** File description:
** player.cpp
*/

#include "../includes/player.hpp"

Player::Player() : _powerOfBomb (1), _numberOfBombs(1), _currentOfBombs(0), _speed(0.05), _throughWalls(false), _alive(true)
{
    _coord.push_back(0);
    _coord.push_back(0);
    _impossible = 0;

}


void Player::increasePower()
{
    _powerOfBomb++;
}

void Player::increaseBombs()
{
    _numberOfBombs++;
}

void Player::increaseSpeed()
{
    _speed += 0.0075;
}

void Player::canThroughWall()
{
    _throughWalls = true;
}

void Player::resetPlayer()
{
    _powerOfBomb = 1;
    _numberOfBombs = 1;
    _currentOfBombs = 0;
    _speed = 0.05;
    _throughWalls = false;
}

Bomb::Bomb(int player, int power, int x, int y) : _player(player), _power(power), _x(x), _y(y)
{
    _start = std::chrono::high_resolution_clock::now();
}
