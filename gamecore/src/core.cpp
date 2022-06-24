/*
** EPITECH PROJECT, 2022
** core.cpp
** File description:
** core.cpp
*/

#include "../includes/core.hpp"

std::vector<std::string> map_generator(size_t width, size_t height);

Core::Core(int nbPlayers) : _nbPlayers(nbPlayers)
{
    _players.push_back(Player());
    _players.push_back(Player());
    _players.push_back(Player());
    _players.push_back(Player());
    _map = map_generator(15, 17);
    for (std::size_t i = 0, p = 1; i < _map.size() && p != 5; i++) {
        for (std::size_t j = 0; j < _map[i].size() && p != 5; j++) {
            if (_map[i][j] == 'V' && p == 4) {
                _players[3]._coord[0] = j;
                _players[3]._coord[1] = i;
                p++;
            }
            if (_map[i][j] == 'V' && p == 3) {
                _players[2]._coord[0] = j;
                _players[2]._coord[1] = i;
                p++;
            }
            if (_map[i][j] == 'V' && p == 2) {
                _players[1]._coord[0] = j;
                _players[1]._coord[1] = i;
                p++;
            }
            if (_map[i][j] == 'V' && p == 1) {
                _players[0]._coord[0] = j;
                _players[0]._coord[1] = i;
                p++;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        inputs.push_back("");
        jobs.push_back(false);
    }
}

void Core::loadMap(char *path)
{
    std::ostringstream oss;
    std::string substring;
    std::stringstream mapNotParse;

    _map.clear();
    std::ifstream file(path, std::ios::in);
    if (file.is_open()) {
        oss << file.rdbuf();
        file.close();
        mapNotParse << oss.str();
        for (int i = 0; mapNotParse.good(); i++) {
            std::getline(mapNotParse, substring, '\n');
            _map.push_back(substring);
        }
    } else {
        std::cerr << "Can't open map !" << std::endl;
        exit(84);
    }
    _map.pop_back();
    _yMax = _map.size();
    _xMax = _map[0].size();
    for (std::size_t i = 0, p = 1; i < _map.size() && p != 5; i++) {
        for (std::size_t j = 0; j < _map[i].size() && p != 5; j++) {
            if (_map[i][j] == 'V' && p == 4) {
                _players[3]._coord[0] = j;
                _players[3]._coord[1] = i;
                p++;
            }
            if (_map[i][j] == 'V' && p == 3) {
                _players[2]._coord[0] = j;
                _players[2]._coord[1] = i;
                p++;
            }
            if (_map[i][j] == 'V' && p == 2) {
                _players[1]._coord[0] = j;
                _players[1]._coord[1] = i;
                p++;
            }
            if (_map[i][j] == 'V' && p == 1) {
                _players[0]._coord[0] = j;
                _players[0]._coord[1] = i;
                p++;
            }
        }
    }
}

float Core::movePlayer(float x, float y, Player *player, int pos)
{
    x *= player->_speed;
    y *= player->_speed;
    if (round(player->_coord[0]) != round(player->_coord[0] + x) ||
        round(player->_coord[1]) != round(player->_coord[1] + y)) {
        if (_map[round(player->_coord[1])][round(player->_coord[0])] == 'V')
            _map[round(player->_coord[1])][round(player->_coord[0])] = '.';
        player->_coord[0] += x;
        player->_coord[1] += y;
        if (_map[round(player->_coord[1])][round(player->_coord[0])] == 'F') {
            _map[round(player->_coord[1])][round(player->_coord[0])] = 'V';
            player->increasePower();
        } else if (_map[round(player->_coord[1])][round(player->_coord[0])] == 'N') {
            _map[round(player->_coord[1])][round(player->_coord[0])] = 'V';
            player->increaseBombs();
        } else if (_map[round(player->_coord[1])][round(player->_coord[0])] == 'S') {
            _map[round(player->_coord[1])][round(player->_coord[0])] = 'V';
            player->increaseSpeed();
        } else if (_map[round(player->_coord[1])][round(player->_coord[0])] == 'W') {
            _map[round(player->_coord[1])][round(player->_coord[0])] = 'V';
            player->canThroughWall();
        } else if (_map[round(player->_coord[1])][round(player->_coord[0])] == '.') {
            _map[round(player->_coord[1])][round(player->_coord[0])] = 'V';
        }
        if (round(player->_coord[0] - 0.5) != round(player->_coord[0] + x - 0.5) ||
            round(player->_coord[1] - 0.5) != round(player->_coord[1] + y - 0.5)) {
            inputs[pos] = "";
            jobs[pos] = true;
        }
        if (x != 0)
            return x;
        else
            return y;
    } else {
        player->_coord[0] += x;
        player->_coord[1] += y;
        if (round(player->_coord[0] - 0.5) != round(player->_coord[0] + x - 0.5) ||
            round(player->_coord[1] - 0.5) != round(player->_coord[1] + y - 0.5)) {
            inputs[pos] = "";
            jobs[pos] = true;
        }
        if (x != 0)
            return x;
        else
            return y;
    }
}

int Core::placeBomb(Player *player, int who)
{
    int x;
    int y;
    int power;

    x = round(player->_coord[0]);
    y = round(player->_coord[1]);
    power = player->_powerOfBomb;
    if (_map[y][x] != 'V' || player->_currentOfBombs == player->_numberOfBombs) {
        inputs[who] = "";
        jobs[who] = true;
        return -1;
    }
    _currentBomb.push_back(Bomb(who, power, x, y));
    player->_currentOfBombs++;
    _map[y][x] = 'B';
    inputs[who] = "";
    jobs[who] = true;
    return 0;
}

float Core::inputInterpretation(const char *input, int player)
{
    std::string command(input);
    float move = -1;

    if (command.compare("UP") == 0) {
        if (player == 1)
            move = movePlayer(0, -1, &_players[0], 0);
        if (player == 2)
            move = movePlayer(0, -1, &_players[1], 1);
        if (player == 3)
            move = movePlayer(0, -1, &_players[2], 2);
        if (player == 4)
            move = movePlayer(0, -1, &_players[3], 3);
    }
    if (command.compare("DOWN") == 0) {
        if (player == 1)
            move = movePlayer(0, 1, &_players[0], 0);
        if (player == 2)
            move = movePlayer(0, 1, &_players[1], 1);
        if (player == 3)
            move = movePlayer(0, 1, &_players[2], 2);
        if (player == 4)
            move = movePlayer(0, 1, &_players[3], 3);
    }
    if (command.compare("LEFT") == 0) {
        if (player == 1)
            move = movePlayer(-1, 0, &_players[0], 0);
        if (player == 2)
            move = movePlayer(-1, 0, &_players[1], 1);
        if (player == 3)
            move = movePlayer(-1, 0, &_players[2], 2);
        if (player == 4) {
            move = movePlayer(-1, 0, &_players[3], 3);
        }
    }
    if (command.compare("RIGHT") == 0) {
        if (player == 1)
            move = movePlayer(1, 0, &_players[0], 0);
        if (player == 2)
            move = movePlayer(1, 0, &_players[1], 1);
        if (player == 3)
            move = movePlayer(1, 0, &_players[2], 2);
        if (player == 4)
            move = movePlayer(1, 0, &_players[3], 3);
    }
    if (command.compare("BOMB") == 0) {
        if (player == 1)
            move = placeBomb(&_players[0], 0);
        if (player == 2)
            move = placeBomb(&_players[1], 1);
        if (player == 3)
            move = placeBomb(&_players[2], 2);
        if (player == 4)
            move = placeBomb(&_players[3], 3);
    }
    return move * 2;
}

void Core::getLoop()
{
    if (_nbPlayers < 1) {
        inputInterpretation(inputs[0].c_str(), 1);
    }
    if (_nbPlayers < 2) {
        inputInterpretation(inputs[1].c_str(), 2);
    }
    if (_nbPlayers < 3) {
        inputInterpretation(inputs[2].c_str(), 3);
    }
    if (_nbPlayers < 4) {
        inputInterpretation(inputs[3].c_str(), 4);
    }
    checkBomb();
}

int Core::checkBombRange(int x, int y)
{
    int powerUp;

    if (round(_players[0]._coord[0]) == x && round(_players[0]._coord[1]) == y) {
        _map[round(_players[0]._coord[1])][round(_players[0]._coord[0])] = '.';
        _players[0]._coord[0] = 0;
        _players[0]._coord[1] = 0;
        _players[0]._alive = false;
    }
    if (round(_players[1]._coord[0]) == x && round(_players[1]._coord[1]) == y) {
        _map[round(_players[1]._coord[1])][round(_players[1]._coord[0])] = '.';
        _players[1]._coord[0] = 0;
        _players[1]._coord[1] = 0;
        _players[1]._alive = false;
    }
    if (round(_players[2]._coord[0]) == x && round(_players[2]._coord[1]) == y) {
        _map[round(_players[2]._coord[1])][round(_players[2]._coord[0])] = '.';
        _players[2]._coord[0] = 0;
        _players[2]._coord[1] = 0;
        _players[2]._alive = false;
    }
    if (round(_players[3]._coord[0]) == x && round(_players[3]._coord[1]) == y) {
        _map[round(_players[3]._coord[1])][round(_players[3]._coord[0])] = '.';
        _players[3]._coord[0] = 0;
        _players[3]._coord[1] = 0;
        _players[3]._alive = false;
    }
    if (_map[y][x] == 'M') {
        if (rand()%10 <= 2) {
            powerUp = rand() % 30;
            if (powerUp < 12)
                _map[y][x] = 'F';
            if (powerUp > 10 && powerUp < 20)
                _map[y][x] = 'N';
            if (powerUp > 19 && powerUp < 29)
                _map[y][x] = 'S';
            if (powerUp == 29)
                _map[y][x] = 'W';
        } else
        _map[y][x] = '.';
        return 1;
    }
    else if (_map[y][x] == 'F' || _map[y][x] == 'N' || _map[y][x] == 'S' || _map[y][x] == 'W')
        _map[y][x] = '.';
    return 0;
}

void Core::checkBomb()
{
    for (std::size_t i = 0; i < _currentBomb.size(); i++) {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - _currentBomb[i]._start;
        if (diff.count() > 3) {
            checkBombRange(_currentBomb[i]._x, _currentBomb[i]._y);
            for (int x1 = 1; x1 < _currentBomb[i]._power + 1 &&
            _map[_currentBomb[i]._y][_currentBomb[i]._x + x1] != '#'; x1++) {
                if (checkBombRange(_currentBomb[i]._x + x1, _currentBomb[i]._y) == 1)
                    break;
            }
            for (int x2 = 1; x2 < _currentBomb[i]._power + 1 &&
            _map[_currentBomb[i]._y][_currentBomb[i]._x - x2] != '#'; x2++) {
                if (checkBombRange(_currentBomb[i]._x - x2, _currentBomb[i]._y) == 1)
                    break;
            }
            for (int y1 = 1; y1 < _currentBomb[i]._power + 1 &&
            _map[_currentBomb[i]._y + y1][_currentBomb[i]._x] != '#'; y1++) {
                if (checkBombRange(_currentBomb[i]._x, _currentBomb[i]._y + y1) == 1)
                    break;
            }
            for (int y2 = 1; y2 < _currentBomb[i]._power + 1 &&
            _map[_currentBomb[i]._y - y2][_currentBomb[i]._x] != '#'; y2++) {
                if (checkBombRange(_currentBomb[i]._x, _currentBomb[i]._y - y2) == 1)
                    break;
            }
            if (_currentBomb[i]._player == 0)
                _players[0]._currentOfBombs--;
            if (_currentBomb[i]._player == 1)
                _players[1]._currentOfBombs--;
            if (_currentBomb[i]._player == 2)
                _players[2]._currentOfBombs--;
            if (_currentBomb[i]._player == 3)
                _players[3]._currentOfBombs--;
            _map[_currentBomb[i]._y][_currentBomb[i]._x] = '.';
            _currentBomb.erase(_currentBomb.begin() + i);
        }
    }
}
