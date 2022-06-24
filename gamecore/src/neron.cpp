#include "../includes/Daedalus.hpp"

Daedalus::Neron::Neron(Core *game, std::vector<float> botPos, int pos)
{
    _bombsMax = 1;
    _bombRadius = 2;
    _pos = {0, 0};
    _targetPos = {-1, -1};
    _index = pos;
    action = 0;
    _fleeing = 0;
    _core = game;
    _map = _core->_map;
    _impossible = _core->_players[_index]._impossible;
    _map[botPos[1]][botPos[0]] = 'P';
    _searchRadius = 10;
    _difficulty = 100;




    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map[i].size(); j++) {
            if (_map[i][j] == 'P') {
                _pos[0] = i;
                _pos[1] = j;
                return;
            }
        }
    }


}

int Daedalus::Neron::myAbs(int val)
{
    if (val < 0)
        return -val;
    return val;
}

int Daedalus::Neron::in_bomb_radius(void)
{

    // size_t distanceNearestBomb = 0;
    // size_t i = 0;
    // size_t j = 0;

    carpet_bomb_map();

    // print _map

    if (_map[_pos[0]][_pos[1]] == 'R' || _map[_pos[0]][_pos[1]] == 'B' || _map[_pos[0]][_pos[1]] == 'J') {
        outdata << "IN BOMB RADIUS\n\n";
        return 1;
    }
    return (0);
}

int Daedalus::Neron::power_up_reachable(void)
{

    std::vector<std::vector<int>> visited;
    std::vector<int> pos = {_pos[0], _pos[1]};
    std::vector<int> PowerupPos = {-1, -1};
    std::pair<int, int> pos_tmp;

    pos_tmp = find_proximity('F', pos, 10); // look for power_ups
    if (pos_tmp.first == -1) {
        pos_tmp = find_proximity('N', pos, 10); // look for power_ups
        if (pos_tmp.first == -1) {
            pos_tmp = find_proximity('S', pos, 10); // look for power_ups
            if (pos_tmp.first == -1)
                return (0);
        }
    }

    PowerupPos[0] = pos_tmp.first;
    PowerupPos[1] = pos_tmp.second;

    _path = find_path(_pos, PowerupPos);
    if (_path.size() == 0)
        return (0);
    return (1);
}

void Daedalus::Neron::get_data(std::vector<std::string> myMap, std::vector<float> newPos)
{
    _map = myMap;
    _pos[0] = newPos[0];
    _pos[1] = newPos[1];
}

std::vector<std::string> Daedalus::Neron::find_path(std::vector<int> start, std::vector<int> end)
{
    aStar path;
    std::vector<std::string> null;
    int a = 0;

    path.mapWidth = _map[0].size();
    path.mapHeight = _map.size();
    if (end[0] <= 0 || end[1] <= 0)
    {
        return (null);
    }


    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map[i].size(); j++) {
            if (_map[i][j] == 'B' && static_cast<int>(i) != _pos[0] && static_cast<int>(j) != _pos[1]) {
                _map[i][j] = 'J';
            }
        }
    }

    if (action == 5)
    {
        if (_map[end[0]][end[1]] == 'M') {
            _map[end[0]][end[1]] = '.';
            a = 1;
        }
        if (_map[start[0]][start[1]] == 'M') {
            _map[start[0]][start[1]] = '.';
            a = 2;
        }
    }

    path.createNode();
    path.setObstacles(_map, _core->_players[_index]._throughWalls);
    path.createConnections(_map, _core->_players[_index]._throughWalls);
    path.setObjectives(start[1], start[0], end[1], end[0]);
    path.aStarSearch();

    std::vector<std::string> dir = path.getPath();
    if (a == 1)
    {
        _map[end[0]][end[1]] = 'M';
        a = 0;
    }
    if (a == 2)
    {
        _map[start[0]][start[1]] = 'M';
        a = 0;
    }
    return (dir);
}

Pair Daedalus::Neron::find_proximity(char tar, std::vector<int> pos, int radius)
{
        std::vector<std::pair<int, int>> proximity;
        std::pair<int, int> tmp = {-1, -1};
        std::vector<int> radiusDif;
        int index = 0;

        if (radius == -1)
            return tmp;

        carpet_bomb_map();

        for (size_t i = 0; i < _map.size(); i++) {
            for (size_t j = 0; j < _map[i].size(); j++) {
                
                if (_map[i][j] == tar) {
                    
                    if (find_path({static_cast<int>(i), static_cast<int>(j)}, pos).size() != 0) { // /Stocker dans une variable pour économiser du temps de calcul
                        proximity.push_back({static_cast<int>(i), static_cast<int>(j)});
                        radiusDif.push_back(find_path({static_cast<int>(i), static_cast<int>(j)}, pos).size());
                    }
                }

            }
        }
    
        if (proximity.empty()) {
            return tmp;
        }
        
        for (size_t i = 0; i < radiusDif.size(); i++)
        {
            if (radiusDif[i] < radiusDif[index])
                index = i;
        }
        
        return (proximity[index]);
}

int Daedalus::Neron::place_bomb(void)
{
    // turns the case you're at into a B and go towards the closest . char
    _map[_pos[0]][_pos[1]] = 'B';
    _core->inputs[_index] = "BOMB";
    
    while (!_core->jobs[_index]); // J'ai finis mon déplacement

    _bombPos.push_back({_pos[0], _pos[1]});
    _core->jobs[_index] = false;
    if (_difficulty >= 50)
        carpet_bomb_map();

    _map[_pos[0]][_pos[1]] = 'R';
    if (_difficulty >= 75)
        flee_bomb();
    else if (rand() % 100 < _difficulty)
        flee_bomb();

    return (0);
}

int Daedalus::Neron::fetch_power_up(void)
{
    return (0);
}

int Daedalus::Neron::player_unreachable(void)
{
    Pair p = find_proximity('V', _pos, _searchRadius);

    if (p.first == -1)
        return (1);
    return (0);
}

int Daedalus::Neron::noBombsMines(void)
{
    if (_map[_pos[0]][_pos[1] + 1] == 'V' || _map[_pos[0]][_pos[1] - 1] == 'V' || _map[_pos[0] + 1][_pos[1]] == 'V' || _map[_pos[0] - 1][_pos[1]] == 'V') {
        if (_core->_players[_index]._numberOfBombs > _core->_players[_index]._currentOfBombs)
            return (1);
    } else {
        if (_core->_players[_index]._currentOfBombs == 0)
            return (1);
    }
    return (0);
}

int Daedalus::Neron::start_searching(void)
{
        // Rajouter une fonction pour chercher si je peux rejoindre un M pour l'éclater et me barrer, ne pas oublier de considérer les M comme des murs
            // Ca permettra d'éviter qu'on se mette à essayer d'atteidre des items à l'autre bout de la map

        while (_core->_players[_index]._currentOfBombs != 0) {
            if (in_bomb_radius() == 1) {
                carpet_bomb_map();
                flee_bomb();
                run_algorithm();
            }
        }

        if (_difficulty >= 60) {
            if (in_bomb_radius() == 1)
                return (3);
            if (power_up_reachable() == 1)
                return (2);
            if (noBombsMines() == 1 && (_map[_pos[0]][_pos[1] + 1] == 'V' || _map[_pos[0]][_pos[1] - 1] == 'V' || _map[_pos[0] + 1][_pos[1]] == 'V' || _map[_pos[0] - 1][_pos[1]] == 'V'))
                return (1);
            if (noBombsMines() == 1 && (_map[_pos[0]][_pos[1] + 1] == 'M' || _map[_pos[0]][_pos[1] - 1] == 'M' || _map[_pos[0] + 1][_pos[1]] == 'M' || _map[_pos[0] - 1][_pos[1]] == 'M'))
                return (1);
        } else {
            if (power_up_reachable() == 1)
                return (2);
            if (in_bomb_radius() == 1)
                return (3);
            if (noBombsMines() == 1 && (_map[_pos[0]][_pos[1] + 1] == 'V' || _map[_pos[0]][_pos[1] - 1] == 'V' || _map[_pos[0] + 1][_pos[1]] == 'V' || _map[_pos[0] - 1][_pos[1]] == 'V'))
                return (1);
            if (noBombsMines() == 1 && (_map[_pos[0]][_pos[1] + 1] == 'M' || _map[_pos[0]][_pos[1] - 1] == 'M' || _map[_pos[0] + 1][_pos[1]] == 'M' || _map[_pos[0] - 1][_pos[1]] == 'M'))
                return (1);
        }

        if (rand() % 100 >= 50 || player_unreachable() == 1) // Penser à srand()
            return (5); /// Détruire les murs destructible
        return (4); // Tuer joueur
}

size_t Daedalus::Neron::find_bomb_rad(int x, int y)
{
    size_t radius = 0;

    for (size_t i = 0; i < _core->_currentBomb.size(); i++) {
        if (_core->_currentBomb[i]._y == x && _core->_currentBomb[i]._x == y) {
            radius = _core->_currentBomb[i]._power + 1;
            return (radius);
        }
    }
    return (3);
}

void Daedalus::Neron::carpet_bomb_map(void)
{
    size_t oldBomb = _bombRadius;

    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map[i].size(); j++) {

            if (_map[i][j] == 'B' || _map[i][j] == 'J') {

                _bombRadius = find_bomb_rad(i, j);
                _bombPos.push_back({static_cast<int>(i), static_cast<int>(j)});
                _map[i][j] = 'R';
                
                for (size_t k = 1; k < _bombRadius && i + k < _map.size(); k++) {
                    if (_map[i + k][j] == '#' || _map[i + k][j] == 'M')
                        break;
                    if (_map[i + k][j] == '.' || _map[i + k][j] == 'P' || _map[i + k][j] == 'V')
                        _map[i + k][j] = 'R';
                }


                for (size_t k = 1; k < _bombRadius && j + k < _map[i].size(); k++) {
                    if (_map[i][j + k] == '#' || _map[i][j + k] == 'M')
                        break;
                    if (_map[i][j + k] == '.' || _map[i][j + k] == 'P' || _map[i][j + k] == 'V')
                        _map[i][j + k] = 'R';
                }
                
                
                for (size_t k = 1; k < _bombRadius && i - k < _map.size(); k++) {
                    if (_map[i - k][j] == '#' || _map[i - k][j] == 'M')
                        break;
                    if (_map[i - k][j] == '.' || _map[i - k][j] == 'P' || _map[i - k][j] == 'V')
                        _map[i - k][j] = 'R';
                }
                
                
                for (size_t k = 1; k < _bombRadius && j - k < _map[i].size(); k++) {
                    if (_map[i][j - k] == '#' || _map[i][j - k] == 'M')
                        break;
                    if (_map[i][j - k] == '.' || _map[i][j - k] == 'P' || _map[i][j - k] == 'V')
                        _map[i][j - k] = 'R';
                }
            }
        }
    }
    _bombRadius = oldBomb;
}

int Daedalus::Neron::flee_bomb(void)
{

    // Find the closest '.' character to 'P'
    std::vector<int> pos = {_pos[0], _pos[1]};
    std::vector<int> targetPos = {-1, -1};
    std::pair<int, int> port;
    std::vector<std::vector<int>> visited;
    std::vector<std::vector<int>> toMove;

    if (_difficulty >= 75)
        carpet_bomb_map();

    port = find_proximity('.', pos, 15);
    targetPos[0] = port.first;
    targetPos[1] = port.second;

    _targetPos = targetPos;
    _path = find_path({_pos[0], _pos[1]}, {targetPos[0], targetPos[1]});
    if (_path.size() == 0)
        return (0);
    _fleeing = 1;
    return (1);
}

int Daedalus::Neron::look_nearest_player(void)

{
    // find the closest V char
    std::vector<int> pos = {_pos[0], _pos[1]};
    std::vector<int> targetPos = {-1, -1};
    std::vector<std::vector<int>> visited;
    std::vector<std::vector<int>> toMove;

    Pair targetPos2 = find_proximity('V', pos, 10);

    targetPos[0] = targetPos2.first;
    targetPos[1] = targetPos2.second;

    if ((targetPos[0] == _pos[0] || targetPos[1] == _pos[1]) && (targetPos[0] - _pos[0] <= static_cast<int>(_bombRadius) || targetPos[1] - _pos[1] <= static_cast<int>(_bombRadius))) {
        place_bomb();
        _path.clear();
        return (1);
    }

    if (targetPos[0] == -1)
        return (-1);

    std::vector<std::string> path = find_path(targetPos, _pos);
    if (path.size() == 0)
        return (-1);
    if (path.front()[0] == 'E')
        targetPos = {targetPos[0], targetPos[1] + 1};
    else if (path.front()[0] == 'O')
        targetPos = {targetPos[0], targetPos[1] - 1};
    else if (path.front()[0] == 'S')
        targetPos = {targetPos[0] + 1, targetPos[1]};
    else if (path.front()[0] == 'N')
        targetPos = {targetPos[0] - 1, targetPos[1]};
    path.clear();
    _path = find_path({_pos[0], _pos[1]}, {targetPos[0], targetPos[1]});
    return (1);
}

void Daedalus::Neron::protocolThreeProtectCoder(void)
{
    std::vector<std::vector<int>> toMove;

    for (size_t path_index = 0; path_index < _path.size(); path_index++) {
        if (_path[path_index][0] == 'N')
            toMove.push_back({_pos[0] - 1, _pos[1]});
        else if (_path[path_index][0] == 'S')
            toMove.push_back({_pos[0] + 1, _pos[1]});
        else if (_path[path_index][0] == 'O')
            toMove.push_back({_pos[0], _pos[1] - 1});
        else if (_path[path_index][0] == 'E')
            toMove.push_back({_pos[0], _pos[1] + 1});
    }

    for (size_t i = 0; i < toMove.size(); i++) {
        if (toMove[i][0] <= 0 || toMove[i][1] <= 0 || toMove[i][1] >= static_cast<int>(_map[0].size()) || toMove[i][0] >= static_cast<int>(_map.size())) {
                std::cout << "Protocol three protect the pilot\n";
            while (1) {
                // std::cout << "ERROR VALUES=" << toMove[i][0] << " " << toMove[i][1] << std::endl;
                place_bomb();
            }
        }
    }
}

void Daedalus::Neron::run_algorithm(void)
{
    std::vector<int> oldPos = _pos;
    std::vector<std::vector<int>> toMove;
    std::vector<char> targs = {'V', 'K'};
    size_t path_index = 0;

    while (path_index < _path.size()) {

        usleep(20000);

        protocolThreeProtectCoder();

        if (_path[path_index][0] == 'N')
            toMove.push_back({_pos[0] - 1, _pos[1]});
        else if (_path[path_index][0] == 'S')
            toMove.push_back({_pos[0] + 1, _pos[1]});
        else if (_path[path_index][0] == 'O')
            toMove.push_back({_pos[0], _pos[1] - 1});
        else if (_path[path_index][0] == 'E')
            toMove.push_back({_pos[0], _pos[1] + 1});

        // Fusionnier les deux if
        if (_path[path_index][0] == 'N')
            _core->inputs[_index] = "UP";
        else if (_path[path_index][0] == 'S')
            _core->inputs[_index] = "DOWN";
        else if (_path[path_index][0] == 'O')
            _core->inputs[_index] = "LEFT";
        else if (_path[path_index][0] == 'E')
            _core->inputs[_index] = "RIGHT";

        while (!_core->jobs[_index]) {
            if (_core->_players[_index]._impossible == 1) {
                _core->_players[_index]._impossible = 0;
                _path.clear();
                toMove.clear();
                return;
            }
        }

        _core->jobs[_index] = false;

        _pos[0] = toMove.back()[0];
        _pos[1] = toMove.back()[1];

        path_index += 1;
        _map = _core->_map;
 
        carpet_bomb_map(); // Faire attention ici il faudra vérifier à le virer
        if (in_bomb_radius() == 1) {
            _path.clear();
            toMove.clear();
            return;
        }


        if (action == 4 && _map[_targetPos[0]][_targetPos[1]] != 'V') {
            look_nearest_player();
            path_index = 0;
        }

        if (action == 2 && _map[_targetPos[0]][_targetPos[1]] != 'K') { // Mettre à jour par rapport aux chars des power ups c'est mal opti
            _path.clear();
            toMove.clear();
            return;
        }
    }

    _path.clear();
    toMove.clear();
}

void Daedalus::Neron::break_wall(void)
{
    std::vector<int> pos = {_pos[0], _pos[1]};
    std::vector<int> targetPos = {-1, -1};
    std::vector<std::vector<int>> visited;
    std::vector<std::vector<int>> toMove;
    Pair p = find_proximity('M', pos, 10);

    if (p.first == -1) {
        return;
    }
    
    _targetPos = {p.first, p.second};
    std::vector<std::string> path = find_path(_targetPos, {_pos[0], _pos[1]});

    if (path.size() == 0) {
        return;
    }
    if (path.front()[0] == 'E')
        targetPos = {p.first, p.second + 1};
    else if (path.front()[0] == 'O')
        targetPos = {p.first, p.second - 1};
    else if (path.front()[0] == 'S')
        targetPos = {p.first + 1, p.second};
    else if (path.front()[0] == 'N')
        targetPos = {p.first - 1, p.second};
    path.clear();
    _path = find_path({_pos[0], _pos[1]}, {targetPos[0], targetPos[1]});
    return;
}

int Daedalus::Neron::play_game(void)
{
    while (_core->_players[_index]._alive) {

        if (_path.empty()) {


            while (_fleeing == 1) {
                _fleeing = 0;
                while (_core->_players[_index]._currentOfBombs != 0) {
                    if (in_bomb_radius() == 1) {
                        _fleeing = 1;
                        carpet_bomb_map();
                        flee_bomb();
                        run_algorithm();
                    }
                }
            }

            _map = _core->_map;
            _map[_pos[0]][_pos[1]] = 'P';
            action = start_searching();

            if (action == 1)
                place_bomb();
            else if (action == 2) // Mettre le path plus haut
                fetch_power_up();
            else if (action == 3)
                flee_bomb();
            else if (action == 4)
                look_nearest_player();
            else if (action == 5)
                break_wall();


        } else {
            action = -1;
            run_algorithm();
        }
    }
    return (0);
}


void Daedalus::Neron::set_difficulty(int difficulty = 100)
{
    _difficulty = difficulty;
}