/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Pacman
*/

#include "Pacman.hpp"

#define FRAME 100

static std::string loadBuffer(std::string filename)
{
    int fd = open(filename.c_str(), O_RDONLY);
    struct stat s;
    char *buf;

    if (fd != -1) {
        fstat(fd, &s);
        buf = (char *) mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (buf == MAP_FAILED) {
            std::cerr << "Mmap failed" << std::endl;
            close(fd);
            return NULL;
        }
    } else {
        std::cerr << "Cannot open :" << filename << std::endl;
        return NULL;
    }
    close(fd);
    return std::string(buf);
}

Pacman::Pacman()
{
    score = 0;
    _list.insert(std::pair<Map_Element ,std::string>(WALL, "Utility/sprites/Group1/Wall.png"));
    _list.insert(std::pair<Map_Element ,std::string>(ITEM1, "Utility/sprites/Group1/Point.png"));
    _list.insert(std::pair<Map_Element ,std::string>(ITEM2, "Utility/sprites/Group1/BigPoint.png"));
    _list.insert(std::pair<Map_Element ,std::string>(VOID, "Utility/sprites/Group1/Void.png"));
    _list.insert(std::pair<Map_Element ,std::string>(PLAYER_HEAD_UP, "Utility/sprites/Group1/PacmanUp.png"));
    _list.insert(std::pair<Map_Element ,std::string>(PLAYER_HEAD_DOWN, "Utility/sprites/Group1/PacmanDown.png"));
    _list.insert(std::pair<Map_Element ,std::string>(PLAYER_HEAD_RIGHT, "Utility/sprites/Group1/PacmanRight.png"));
    _list.insert(std::pair<Map_Element ,std::string>(PLAYER_HEAD_LEFT, "Utility/sprites/Group1/PacmanLeft.png"));
    _list.insert(std::pair<Map_Element ,std::string>(ENEMY, "Utility/sprites/Group1/Ennemy.png"));
    _list.insert(std::pair<Map_Element ,std::string>(ENEMY_VULNERABLE, "Utility/sprites/Group1/EnnemyVulnerable.png"));
    loadMap("./Utility/maps/Group1/PacmanMap.txt");
    loadMapVector();
    _posx = 13;
    _posy = 22;
    vulnerable = false;
    _isEnd = false;
    _isGod = false;
    std::srand(std::time(nullptr));
    _timer = std::chrono::system_clock::now();
    _ghostPosition = {{13, 12}, {13, 13}, {14, 13}};
    ghost_handling = {{{G_NONE, false}, {13, 12}}, {{G_NONE, false}, {13, 13}}, {{G_NONE, false}, {14, 13}}};
    _saveObj = {{VOID, {13, 12}}, {VOID, {13, 13}}, {VOID, {14, 13}}};
}

Pacman::~Pacman()
{
}

void Pacman::loadMapVector()
{
    std::vector<Map_Element> temp;
    for (auto &it : _map) {
        for (auto &ite : it)
            temp.push_back(ite);
        _mapVector.push_back(temp);
        temp.clear();
    }
}

void Pacman::loadMap(std::string filename)
{
    std::string buffer = loadBuffer(filename);
    std::list<Map_Element> _line;

    for (auto &n : buffer) {
        if (n == '#') {
            _line.push_back(WALL);
        } else if (n == '*') {
            _line.push_back(ITEM1);
        } else if (n == 'o') {
            _line.push_back(ITEM2);
        } else if (n == 'E') {
            _line.push_back(ENEMY);
        } else if (n == 'P') {
            _line.push_back(PLAYER_HEAD_UP);
        } else if (n == ' ') {
            _line.push_back(VOID);
        } else if (n == '\n') {
            _map.push_back(_line);
            _line.erase(_line.begin(), _line.end());
        }
    }
    _map.push_back(_line);
}

void Pacman::setMaptoMapVector()
{
    int x, y = 0;
    for (auto &it : _map) {
        x = 0;
        for (auto &ite : it) {
            ite = _mapVector[y][x];
            x++;
        }
        y++;
    }
}

void Pacman::beginTheCourse()
{
    int dir;
    for (auto &it : ghost_handling) {
        if (!it.first.second) {
            dir = std::rand() / ((RAND_MAX + 1u) / 4);
            if (dir == 0) {
                it.first.first = G_LEFT;
            } else if (dir == 1) {
                it.first.first = G_UP;
            } else if (dir == 2) {
                it.first.first = G_RIGHT;
            } else if (dir == 3) {
                it.first.first = G_DOWN;
            }
        }
    }
}

bool Pacman::refactoMoveGhostRight(int index) {
    std::pair <Map_Element, std::pair<int, int>> temp;
    Map_Element tmp = _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first + 1];
    if (tmp != WALL && tmp != ENEMY && tmp != ENEMY_VULNERABLE) {
        if (tmp == PLAYER_HEAD_LEFT || tmp == PLAYER_HEAD_RIGHT || tmp == PLAYER_HEAD_UP || tmp == PLAYER_HEAD_DOWN) {
            if (_mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first] == ENEMY) {
                _isEnd = true;
                return true;
            } else if (_mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first] == ENEMY_VULNERABLE) {
                resetGhost(1, 0);
                return true;
            }
        }
        temp.first = _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first + 1];
        ghost_handling[index].first.first = G_RIGHT;
        temp.second.first = ghost_handling[index].second.first + 1;
        temp.second.second = ghost_handling[index].second.second;
        _saveObj.insert(_saveObj.begin(), temp);
        _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first + 1] =
                _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first];
        _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first] =
                getSaveObj(ghost_handling[index].second.first, ghost_handling[index].second.second);
        ghost_handling[index].second.first += 1;
        return true;
    }
    return false;
}

bool Pacman::refactoMoveGhostLeft(int index)
{
    std::pair<Map_Element, std::pair<int, int>> temp;
    Map_Element tmp = _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first - 1];
    if (tmp != WALL && tmp != ENEMY && tmp != ENEMY_VULNERABLE) {
        if (tmp == PLAYER_HEAD_LEFT || tmp == PLAYER_HEAD_RIGHT || tmp == PLAYER_HEAD_UP || tmp == PLAYER_HEAD_DOWN) {
            if (_mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first] == ENEMY) {
                _isEnd = true;
                return true;
            } else if (_mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first] == ENEMY_VULNERABLE) {
                resetGhost(-1, 0);
                return true;
            }
        }
        temp.first = _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first - 1];
        ghost_handling[index].first.first = G_LEFT;
        temp.second.first = ghost_handling[index].second.first - 1;
        temp.second.second = ghost_handling[index].second.second;
        _saveObj.insert(_saveObj.begin(), temp);
        _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first - 1] =
                _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first];
        _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first] =
                getSaveObj(ghost_handling[index].second.first, ghost_handling[index].second.second);
        ghost_handling[index].second.first -= 1;
        return true;
    }
    return false;
}

bool Pacman::refactoMoveGhostUp(int index)
{
    std::pair<Map_Element, std::pair<int, int>> temp;
    Map_Element tmp = _mapVector[ghost_handling[index].second.second - 1][ghost_handling[index].second.first];
    if (tmp != WALL && tmp != ENEMY && tmp != ENEMY_VULNERABLE) {
        if (tmp == PLAYER_HEAD_LEFT || tmp == PLAYER_HEAD_RIGHT || tmp == PLAYER_HEAD_UP || tmp == PLAYER_HEAD_DOWN) {
            if (_mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first] == ENEMY) {
                _isEnd = true;
                return true;
            } else if (_mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first] == ENEMY_VULNERABLE) {
                resetGhost(0, -1);
                return true;
            }
        }
        temp.first = _mapVector[ghost_handling[index].second.second - 1][ghost_handling[index].second.first];
        ghost_handling[index].first.first = G_UP;
        temp.second.first = ghost_handling[index].second.first;
        temp.second.second = ghost_handling[index].second.second - 1;
        _saveObj.insert(_saveObj.begin(), temp);
        _mapVector[ghost_handling[index].second.second - 1][ghost_handling[index].second.first] =
                _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first];
        _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first] =
                getSaveObj(ghost_handling[index].second.first, ghost_handling[index].second.second);
        ghost_handling[index].second.second -= 1;
        return true;
    }
    return false;
}

bool Pacman::refactoMoveGhostDown(int index)
{
    std::pair<Map_Element, std::pair<int, int>> temp;
    Map_Element tmp = _mapVector[ghost_handling[index].second.second + 1][ghost_handling[index].second.first];
    if (tmp != WALL && tmp != ENEMY && tmp != ENEMY_VULNERABLE) {
        if (tmp == PLAYER_HEAD_LEFT || tmp == PLAYER_HEAD_RIGHT || tmp == PLAYER_HEAD_UP || tmp == PLAYER_HEAD_DOWN) {
            if (_mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first] == ENEMY) {
                _isEnd = true;
                return true;
            } else if (_mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first] == ENEMY_VULNERABLE) {
                resetGhost(0, 1);
                return true;
            }
        }
        temp.first = _mapVector[ghost_handling[index].second.second + 1][ghost_handling[index].second.first];
        ghost_handling[index].first.first = G_DOWN;
        temp.second.first = ghost_handling[index].second.first;
        temp.second.second = ghost_handling[index].second.second + 1;
        _saveObj.insert(_saveObj.begin(), temp);
        _mapVector[ghost_handling[index].second.second + 1][ghost_handling[index].second.first] =
                _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first];
        _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first] =
                getSaveObj(ghost_handling[index].second.first, ghost_handling[index].second.second);
        ghost_handling[index].second.second += 1;
        return true;
    }
    return false;
}

bool Pacman::gotIntersection(int index)
{
    Map_Element tmpRight;
    Map_Element tmpLeft;
    Map_Element tmpDown;
    Map_Element tmpUp;

    if (ghost_handling[index].second.first + 1 > 26 || ghost_handling[index].second.first - 1 < 0
        || ghost_handling[index].second.second + 1 > 26 || ghost_handling[index].second.first - 1 < 0)
        return false;
    tmpRight = _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first + 1];
    tmpLeft = _mapVector[ghost_handling[index].second.second][ghost_handling[index].second.first - 1];
    tmpDown = _mapVector[ghost_handling[index].second.second + 1][ghost_handling[index].second.first];
    tmpUp = _mapVector[ghost_handling[index].second.second - 1][ghost_handling[index].second.first];
    int chance = 0;

    if (tmpRight != WALL && tmpRight != ENEMY && tmpRight != ENEMY_VULNERABLE)
        chance++;
    if (tmpLeft != WALL && tmpLeft != ENEMY && tmpLeft != ENEMY_VULNERABLE)
        chance++;
    if (tmpDown != WALL && tmpDown != ENEMY && tmpDown != ENEMY_VULNERABLE)
        chance++;
    if (tmpUp != WALL && tmpUp != ENEMY && tmpUp != ENEMY_VULNERABLE)
        chance++;
    if (chance > 2) {
        return true;
    }
    return false;
}

Map_Element Pacman::getSaveObj(int x, int y)
{
    Map_Element temp;
    for (auto it = _saveObj.begin(); it != _saveObj.end(); it++) {
        if (it->second.first == x && it->second.second == y) {
            temp = it->first;
            _saveObj.erase(it);
            return temp;
        }
    }
    return VOID;
}

void Pacman::randomDir(int index)
{
    int dir;
    bool isPassed = false;
    while (!isPassed) {
        dir = std::rand() / ((RAND_MAX + 1u) / 4);
        if (dir == 0)
            isPassed = refactoMoveGhostLeft(index);
        else if (dir == 1)
            isPassed = refactoMoveGhostUp(index);
        else if (dir == 2)
            isPassed = refactoMoveGhostRight(index);
        else if (dir == 3)
            isPassed = refactoMoveGhostDown(index);
    }
}

bool Pacman::exceptCase(int index)
{
    std::pair<Map_Element, std::pair<int, int>> temp;
    if (ghost_handling[index].second.first == 13 && ghost_handling[index].second.second == 12) {
        refactoMoveGhostUp(index);
        return true;
    }
    if (ghost_handling[index].second.first == 26 && ghost_handling[index].second.second == 13
    && ghost_handling[index].first.first != G_LEFT) {
        temp.first = _mapVector[13][0];
        temp.second.first = 0;
        temp.second.second = 13;
        _saveObj.insert(_saveObj.begin(), temp);
        _mapVector[13][0] = _mapVector[13][26];
        _mapVector[13][26] = getSaveObj(26, 13);
        ghost_handling[index].first.first = G_RIGHT;
        ghost_handling[index].second.first = 0;
        ghost_handling[index].second.second = 13;
        return true;
    }
    else if (ghost_handling[index].second.first == 0 && ghost_handling[index].second.second == 13
        && ghost_handling[index].first.first != G_RIGHT) {
        temp.first = _mapVector[13][26];
        temp.second.first = 26;
        temp.second.second = 13;
        _saveObj.insert(_saveObj.begin(), temp);
        _mapVector[13][26] = _mapVector[13][0];
        _mapVector[13][0] = getSaveObj(0, 13);
        ghost_handling[index].first.first = G_LEFT;
        ghost_handling[index].second.first = 26;
        ghost_handling[index].second.second = 13;
        return true;
    }
    return false;
}

void Pacman::moveGhost()
{
    if (!ghost_handling[0].first.second || !ghost_handling[1].first.second || !ghost_handling[2].first.second)
        beginTheCourse();

    for (int i = 0; i < 3; i++) {
        if (ghost_handling[i].first.second) {
            if (exceptCase(i));
            else if (gotIntersection(i)) {
                randomDir(i);
            } else if (ghost_handling[i].first.first == G_LEFT) {
                if (!refactoMoveGhostLeft(i))
                    randomDir(i);
            } else if (ghost_handling[i].first.first == G_UP) {
                if (!refactoMoveGhostUp(i))
                    randomDir(i);
            } else if (ghost_handling[i].first.first == G_RIGHT) {
                if (!refactoMoveGhostRight(i))
                    randomDir(i);
            } else if (ghost_handling[i].first.first == G_DOWN) {
                if (!refactoMoveGhostDown(i))
                    randomDir(i);
            }
        }
    }
}

void Pacman::fearGhost()
{
    for (auto &it: _mapVector)
        for (auto &ite : it)
            if (ite == ENEMY)
                ite = ENEMY_VULNERABLE;
}

void Pacman::unfearGhost()
{
    for (auto &it: _mapVector)
        for (auto &ite : it)
            if (ite == ENEMY_VULNERABLE)
                ite = ENEMY;
}

void Pacman::resetGhost(int x, int y)
{
    std::pair<Map_Element, std::pair<int, int>> temp;
    int i = 0;
    for (auto &it : ghost_handling) {
        if (it.second.first == _posx + x && it.second.second == _posy + y) {
            it.first.second = false;
            temp.first = _mapVector[it.second.second][it.second.first];
            temp.second.first = it.second.first;
            temp.second.second = it.second.second;
            _saveObj.insert(_saveObj.begin(), temp);
            _mapVector[it.second.second][it.second.first] = getSaveObj(it.second.first, it.second.second);
            it.second.first = _ghostPosition[i].first;
            it.second.second = _ghostPosition[i].second;
            _mapVector[it.second.second][it.second.first] = temp.first;
        }
        i++;
    }
}

void Pacman::refactoMovePLayer(int y, int x, Map_Element player)
{
    Map_Element next = _mapVector[_posy + y][_posx + x];
    if (next != WALL) {
        if (next == ENEMY)
            _isEnd = true;
        else if (next == ENEMY_VULNERABLE) {
            resetGhost(x, y);
            _mapVector[_posy + y][_posx + x] = player;
            _mapVector[_posy][_posx] = VOID;
            _posy += y;
            _posx += x;
        }
        else {
            _mapVector[_posy + y][_posx + x] = player;
            _mapVector[_posy][_posx] = VOID;
            _posy += y;
            _posx += x;
        }
    }
    if (next == ITEM2) {
        _isGod = true;
        fearGhost();
    }
    if (next == ITEM1)
        ++score;
}

bool Pacman::exceptionMove(int x)
{
    if (_posx == 0 && _posy == 13 && x == -1) {
        _posx = 26;
        _posy = 13;
        _mapVector[13][0] = VOID;
        _mapVector[13][26] = PLAYER_HEAD_LEFT;
        return true;
    }
    else if (_posx == 26 && _posy == 13 && x == 1) {
        _posx = 0;
        _posy = 13;
        _mapVector[13][26] = VOID;
        _mapVector[13][0] = PLAYER_HEAD_RIGHT;
        return true;
    }
    return false;
}

void Pacman::moovePlayer()
{
    Map_Element player = getMap_Elem(_posy, _posx);

    if (player == PLAYER_HEAD_UP)
        refactoMovePLayer((-1), 0, player);
    if (player == PLAYER_HEAD_DOWN)
        refactoMovePLayer(1, 0, player);
    if (player == PLAYER_HEAD_LEFT) {
        if (!exceptionMove(-1))
            refactoMovePLayer(0, (-1), player);
    }
    if (player == PLAYER_HEAD_RIGHT) {
        if (!exceptionMove(1))
            refactoMovePLayer(0, 1, player);
    }
}

void Pacman::ghostWaitingRoom()
{
    static int first = 0;
    static int second = 0;
    static int third = 0;
    int i = 0;
    for (auto &it : ghost_handling) {
        if (!it.first.second && i == 0) {
            first++;
            if (first == 10) {
                first = 0;
                it.first.second = true;
            }
        }
        if (!it.first.second && i == 1) {
            second++;
            if (second == 10) {
                second = 0;
                it.first.second = true;
            }
        }
        if (!it.first.second && i == 2) {
            third++;
            if (third == 10) {
                third = 0;
                it.first.second = true;
            }
        }
        i++;
    }
}

void Pacman::update()
{
    static int countVulnerable = 0;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - _timer;
    if (elapsed.count() >= 0.35) {
        ghostWaitingRoom();
        if (countVulnerable == 22) {
            _isGod = false;
            countVulnerable = 0;
            unfearGhost();
        }
        if (_isGod)
            countVulnerable++;
        moovePlayer();
        moveGhost();
        setMaptoMapVector();
        _timer = std::chrono::system_clock::now();
    }
}

void Pacman::reset()
{
    _isEnd = false;
    _isGod = false;
    score = 0;
    _map.erase(_map.begin(), _map.end());
    _mapVector.clear();
    loadMap("./Utility/maps/Group1/PacmanMap.txt");
    loadMapVector();
    _posx = 13;
    _posy = 22;
    _ghostPosition = {{13, 12}, {13, 13}, {14, 13}};
    ghost_handling = {{{G_NONE, false}, {13, 12}}, {{G_NONE, false}, {13, 13}}, {{G_NONE, false}, {14, 13}}};
    _saveObj = {{VOID, {13, 12}}, {VOID, {13, 13}}, {VOID, {14, 13}}};
    _timer = std::chrono::system_clock::now();
}

int Pacman::getScore()
{
    return score;
}

std::list<std::list<Map_Element>> Pacman::getMap()
{
    return _map;
}

Map_Element Pacman::getMap_Elem(int y, int x)
{
    int tmp_y = 0;
    int tmp_x = 0;

    for (auto &n : _map) {
        if (tmp_y == y) {
            for (auto &n2 : n) {
                if (tmp_x == x) {
                    return (n2);
                }
                tmp_x++;
            }
        }
        tmp_x = 0;
        tmp_y++;
    }
    return Map_Element::VOID;
}

void Pacman::changePlayer(Map_Element player)
{
    int tmp_y = 0;
    int tmp_x = 0;

    for (auto &n : _map) {
        if (tmp_y == _posy) {
            for (auto &n2 : n) {
                if (tmp_x == _posx)
                    n2 = player;
                tmp_x++;
            }
        }
        tmp_y++;
    }
}

void Pacman::makeAction(Events event)
{
    if (event == UP) {
        changePlayer(PLAYER_HEAD_UP);
    } else if (event == DOWN) {
        changePlayer(PLAYER_HEAD_DOWN);
    } else if (event == LEFT) {
        changePlayer(PLAYER_HEAD_LEFT);
    } else if (event == RIGHT) {
        changePlayer(PLAYER_HEAD_RIGHT);
    }
}

std::map<Map_Element, std::string> Pacman::getAssets()
{
    return (_list);
}

bool Pacman::isEnd()
{
    return (_isEnd);
}

extern "C" std::shared_ptr<IGames> gameEntrypoint()
{
    return std::shared_ptr<IGames>(new Pacman());
}
