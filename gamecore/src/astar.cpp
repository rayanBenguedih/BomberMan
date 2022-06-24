#include "../includes/Daedalus.hpp"

Daedalus::cell::cell() : parent(-1, -1), f(-1), g(-1), h(-1)
{
}

void Daedalus::aStar::createNode()
{
    nodesArray = new Snode[mapWidth * mapHeight];

    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            nodesArray[y * mapWidth + x].x = x;
            nodesArray[y * mapWidth + x].y = y;
            nodesArray[y * mapWidth + x].obstacle = false;
            nodesArray[y * mapWidth + x].parent = nullptr;
            nodesArray[y * mapWidth + x].visited = false;
        }
    }
}

void Daedalus::aStar::setObstacles(std::vector<std::string> map, bool pass)
{
    for (int x = 0; x < mapWidth; x++) {
        for (int y = 0; y < mapHeight; y++) {
            
            if (pass == false) {
                if (map[y][x] == 'M') {
                    nodesArray[y * mapWidth + x].obstacle = true;
                }
            }
            
            if (map[y][x] == '#' || map[y][x] == 'J') {
                nodesArray[y * mapWidth + x].obstacle = true;
            }
        }
    }
}


void Daedalus::aStar::createConnections(std::vector<std::string> map, bool pass)
{

    for (int x = 0; x < mapWidth; x++) {
        for (int y = 0; y < mapHeight; y++) {
            if (pass == false) {
                if (map[y][x] == 'M')
                    continue;
            }
            if (map[y][x] == '#' || map[y][x] == 'J')
                continue;
            else {
                if (x > 0)
                    nodesArray[y * mapWidth + x].neighbors.push_back(&nodesArray[y * mapWidth + (x - 1)]);
                if (x < mapWidth - 1)
                    nodesArray[y * mapWidth + x].neighbors.push_back(&nodesArray[y * mapWidth + (x + 1)]);
                if (y > 0)
                    nodesArray[y * mapWidth + x].neighbors.push_back(&nodesArray[(y - 1) * mapWidth + x]);
                if (y < mapHeight - 1)
                    nodesArray[y * mapWidth + x].neighbors.push_back(&nodesArray[(y + 1) * mapWidth + x]);
            }
        }
    }
}

void Daedalus::aStar::setObjectives(int startX, int startY, int endX, int endY)
{
    nodeStart = &nodesArray[startY * mapWidth + startX];
    nodeEnd = &nodesArray[endY * mapWidth + endX];
}


float Daedalus::aStar::distance(Snode *node1, Snode *node2)
{
    return sqrt(pow(node1->x - node2->x, 2) + pow(node1->y - node2->y, 2));
}

float Daedalus::aStar::heuristic(Snode *node1, Snode *node2)
{
    return distance(node1, node2);
}

void Daedalus::aStar::aStarSearch(void)
{
    Snode *nodeCurrent = nodeStart;
    std::list<Snode *> openList;

    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            nodesArray[y * mapWidth + x].fGlobal = std::numeric_limits<float>::infinity();
            nodesArray[y * mapWidth + x].fLocal = std::numeric_limits<float>::infinity();
        }
    }

    nodeStart->fGlobal = heuristic(nodeStart, nodeEnd);
    nodeStart->fLocal = 0;

    openList.push_back(nodeStart);

    while (!openList.empty() && nodeCurrent != nodeEnd)
    {
        openList.sort([](Snode *node1, Snode *node2)
                      { return node1->fGlobal < node2->fGlobal; });

        while (!openList.empty() && openList.front()->visited)
        {
            openList.pop_front();
        }

        if (openList.empty())
            break;

        nodeCurrent = openList.front();
        nodeCurrent->visited = true;

        for (auto Neighbour : nodeCurrent->neighbors)
        {
            if (!Neighbour->visited && Neighbour->obstacle == false)
            {
                openList.push_back(Neighbour);
            }

            float newFGlobal = nodeCurrent->fGlobal + distance(nodeCurrent, Neighbour);

            if (newFGlobal < Neighbour->fGlobal)
            {
                Neighbour->parent = nodeCurrent;
                Neighbour->fLocal = newFGlobal;
                Neighbour->fGlobal = Neighbour->fLocal + distance(Neighbour, nodeEnd);
            }
        }
    }
}

std::vector<std::string> Daedalus::aStar::getPath(void)
{

    Snode *p = nodeEnd;
    Snode *p2;
    std::vector<std::string> path;

    while (p != nullptr && p->parent != nullptr) {
        p2 = p;
        p = p->parent;
        if (p2->x == p->x) {
            
            if (p2->y > p->y) {
                path.push_back("S");
            } else {
                path.push_back("N");
            }
        
        } else if (p2->y == p->y) {
           
            if (p2->x > p->x) {
                path.push_back("E");
            } else {
                path.push_back("O");
            }

        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}