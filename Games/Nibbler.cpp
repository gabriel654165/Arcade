/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

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

void Nibbler::loadMap(std::string filename)
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
        } else if (n == 'B') {
            _line.push_back(PLAYER_BODY);
        } else if (n == 'N') {
            _line.push_back(PLAYER_END);
        } else if (n == ' ') {
            _line.push_back(VOID);
        } else if (n == '\n') {
            _map.push_back(_line);
            _line.erase(_line.begin(), _line.end());
        }
    }
    _map.push_back(_line);
}

Nibbler::Nibbler()
{
    score = 0;

    _list.insert(std::pair<Map_Element ,std::string>(WALL, "Utility/sprites/Group1/Wall.png"));
    _list.insert(std::pair<Map_Element ,std::string>(ITEM1, "Utility/sprites/Group1/Point.png"));
    _list.insert(std::pair<Map_Element ,std::string>(ITEM2, "Utility/sprites/Group1/peach.png"));
    _list.insert(std::pair<Map_Element ,std::string>(PLAYER_BODY, "Utility/sprites/Group1/serpent_body.png"));
    _list.insert(std::pair<Map_Element ,std::string>(VOID, "Utility/sprites/Group1/Void.png"));
    _list.insert(std::pair<Map_Element ,std::string>(PLAYER_HEAD_UP, "Utility/sprites/Group1/serpent_up.png"));
    _list.insert(std::pair<Map_Element ,std::string>(PLAYER_HEAD_DOWN, "Utility/sprites/Group1/serpent_down.png"));
    _list.insert(std::pair<Map_Element ,std::string>(PLAYER_HEAD_RIGHT, "Utility/sprites/Group1/serpent_right.png"));
    _list.insert(std::pair<Map_Element ,std::string>(PLAYER_HEAD_LEFT, "Utility/sprites/Group1/serpent_left.png"));
    _list.insert(std::pair<Map_Element ,std::string>(PLAYER_END, "Utility/sprites/Group1/serpent_end.png"));
    _list.insert(std::pair<Map_Element ,std::string>(ENEMY, "Utility/sprites/Group1/Ennemy.png"));
    loadMap("./Utility/maps/Group1/NibblerMap.txt");
    _isEnd = false;
    std::pair<int, int> init = getPlayer_pos();
    std::pair<int, int> init2 = std::make_pair(init.first, (init.second + 1));
    std::pair<int, int> init3 = std::make_pair(init2.first, (init2.second + 1));
    std::pair<int, int> init4 = std::make_pair(init3.first, (init3.second + 1));

    _snake.push_back(init);
    _snake.push_back(init2);
    _snake.push_back(init3);
    _snake.push_back(init4);
    _frame = 0.240;
    _timer = std::chrono::system_clock::now();
    _timer_fruit = std::chrono::system_clock::now();


}

Nibbler::~Nibbler()
{

}

void Nibbler::update()
{
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - _timer;
    std::chrono::duration<double> elapsed_fruit = end - _timer_fruit;
    std::pair<int, int> item;

    if (elapsed_fruit.count() > 8) {
        item = getItem_pos();
        changeMap(item.first, item.second, VOID);
        generateFruit_on_map();
    }

    if (elapsed.count() > _frame) {
        mooveSnake();
        _timer = std::chrono::system_clock::now();
    }
}

std::pair<int, int> Nibbler::getItem_pos()
{
    int tmp_y = 0;
    int tmp_x = 0;

    for (auto &n : _map) {

        for (auto &n2 : n) {
            if (n2 == ITEM1 || n2 == ITEM2)
                return (std::make_pair(tmp_y, tmp_x));
            tmp_x++;
        }
        tmp_y++;
        tmp_x = 0;
    }
    return (std::make_pair((-1), (-1)));
}

void Nibbler::reset()
{
    _map.erase(_map.begin(), _map.end());
    loadMap("./Utility/maps/Group1/NibblerMap.txt");
    _snake.clear();
    std::pair<int, int> init = getPlayer_pos();
    std::pair<int, int> init2 = std::make_pair(init.first, (init.second + 1));
    std::pair<int, int> init3 = std::make_pair(init2.first, (init2.second + 1));
    std::pair<int, int> init4 = std::make_pair(init3.first, (init3.second + 1));

    _snake.push_back(init);
    _snake.push_back(init2);
    _snake.push_back(init3);
    _snake.push_back(init4);
    _isEnd = false;
    score = 0;
    _frame = 0.240;
    _timer = std::chrono::system_clock::now();
    _timer_fruit = std::chrono::system_clock::now();

}

int Nibbler::getScore()
{
    return score;
}
std::list<std::list<Map_Element>> Nibbler::getMap()
{
    return _map;
}

std::pair<int, int> Nibbler::getPlayer_pos()
{
    int tmp_y = 0;
    int tmp_x = 0;

    for (auto &n : _map) {

        for (auto &n2 : n) {
            if (n2 >= PLAYER_HEAD_UP && n2 <= PLAYER_HEAD_RIGHT)
                return (std::make_pair(tmp_y, tmp_x));
            tmp_x++;
        }
        tmp_y++;
        tmp_x = 0;
    }
    return (std::make_pair((-1), (-1)));
}

void Nibbler::mooveSnake()
{
    Map_Element player = getMap_Elem(_snake[0].first, _snake[0].second);

    if (player == PLAYER_HEAD_UP)
        mooveHead((-1), 0);
    if (player == PLAYER_HEAD_DOWN)
        mooveHead(1, 0);
    if (player == PLAYER_HEAD_LEFT)
        mooveHead(0, (-1));
    if (player == PLAYER_HEAD_RIGHT)
        mooveHead(0, 1);
}

void Nibbler::mooveHead(int y, int x)
{
    std::pair<int, int> tmp_pos;
    Map_Element next = getMap_Elem(_snake[0].first + y, _snake[0].second + x);
    Map_Element head = getMap_Elem(_snake[0].first, _snake[0].second);

    if (next != VOID && next != ITEM1 && next != ITEM2) {
        _isEnd = true;
        return ;
    }
    int size = _snake.size();
    if (size > 1) {
        tmp_pos.first = _snake[size - 1].first;
        tmp_pos.second = _snake[size - 1].second;
        for (int i = (size - 1); i > 0; i--) {
            _snake[i].first = _snake[i - 1].first;
            _snake[i].second = _snake[i - 1].second;
        }
        _snake[0].first += y;
        _snake[0].second += x;
    } else {
        tmp_pos.first = _snake[0].first;
        tmp_pos.second = _snake[0].second;
        _snake[0].first = _snake[0].first + y;
        _snake[0].second = _snake[0].second + x;
    }
    if (next == ITEM1) {
        change_score(next);
        change_frame_rate();
        generateFruit_on_map();
        _snake.push_back(tmp_pos);
        clear_snake_on_Map();
        add_snake_on_Map(head);
    } else if (next == ITEM2) {
        change_score(next);
        change_frame_rate();
        generateFruit_on_map();
        _snake.push_back(tmp_pos);
        tmp_pos = check_around(tmp_pos);
        _snake.push_back(tmp_pos);
        clear_snake_on_Map();
        add_snake_on_Map(head);
    } else if (next == VOID) {
        clear_snake_on_Map();
        add_snake_on_Map(head);
    }
}

void Nibbler::change_frame_rate()
{
    if (_frame >= 0.140)
        _frame -= 0.01;
    else if (_frame < 0.140 && _frame >= 0.080)
        _frame -= 0.005;
    else if (_frame < 0.080 && _frame >= 0.020)
        _frame -= 0.0025;
}

void Nibbler::change_score(Map_Element elem)
{
    if (elem == ITEM1) {
        if (_frame >= 0.250)
            score = score;
        else if (_frame < 0.250 && _frame >= 0.140)
            score += 1;
        else if (_frame < 0.140 && _frame >= 0.080)
            score += 2;
        else if (_frame < 0.080 && _frame >= 0.020)
            score += 3;
        else
            score +=  4;
    } else if (elem == ITEM2) {
        if (_frame >= 0.250)
            score = score;
        else if (_frame  < 0.250 && _frame >= 0.140)
            score += 2;
        else if (_frame < 0.140 && _frame >= 0.080)
            score += 4;
        else if (_frame < 0.080 && _frame >= 0.020)
            score += 6;
        else
            score += 8;
    }
}

std::pair<int, int> Nibbler::check_around(std::pair<int, int> tmp)
{
    if (getMap_Elem(tmp.first + 1, tmp.second) == VOID)
        return (std::make_pair(tmp.first + 1, tmp.second));
    if (getMap_Elem(tmp.first - 1, tmp.second) == VOID)
        return (std::make_pair(tmp.first - 1, tmp.second));
    if (getMap_Elem(tmp.first, tmp.second + 1) == VOID)
        return (std::make_pair(tmp.first, tmp.second + 1));
    if (getMap_Elem(tmp.first, tmp.second - 1) == VOID)
        return (std::make_pair(tmp.first, tmp.second - 1));
    else 
        return (std::make_pair(-1, -1));
}

void Nibbler::clear_snake_on_Map()
{
    for (auto &n : _map) {
        for (auto &n2 : n) {
            if (n2 >= PLAYER_HEAD_UP && n2 <= PLAYER_END) {
                n2 = VOID;
            }
        }
    }
}

void Nibbler::generateFruit_on_map()
{
    int tmp_y = 0;
    int tmp_x = 0;
    std::vector<std::pair<int, int>> coords;
    _timer_fruit = std::chrono::system_clock::now();

    for (auto &n : _map) {
        for (auto &n2 : n) {
            if (n2 == VOID) {
                coords.push_back(std::make_pair(tmp_y, tmp_x));
            }
            tmp_x++;
        }
        tmp_x = 0;
        tmp_y++;
    }
    int size = coords.size();
    if (size > 0) {
        int index = std::rand() % size;
        if (score % 10 == 0 && score > 10)
            changeMap(coords[index].first, coords[index].second, ITEM2);
        else
        changeMap(coords[index].first, coords[index].second, ITEM1);
    }
    coords.clear();
}

void Nibbler::add_snake_on_Map(Map_Element head)
{
    int size = _snake.size();

    if (size > 2) {
        changeMap(_snake[0].first, _snake[0].second, head);
        changeMap(_snake[size - 1].first, _snake[size - 1].second, PLAYER_END);
        for (int i = size - 2; i > 0; i--) {
            changeMap(_snake[i].first, _snake[i].second, PLAYER_BODY);
        }
    } else if (size == 2) {
        changeMap(_snake[0].first, _snake[0].second, head);
        changeMap(_snake[1].first, _snake[1].second, PLAYER_END);
    } else {
        changeMap(_snake[0].first, _snake[0].second, head);
    }
}

void Nibbler::changeMap(int y, int x, Map_Element elem)
{
    int tmp_y = 0;
    int tmp_x = 0;

    for (auto &n : _map) {
        if (tmp_y == y) {
            for (auto &n2 : n) {
                if (tmp_x == x) {
                    n2 = elem;
                }
                tmp_x++;
            }
        }
        tmp_x = 0;
        tmp_y++;
    }
}

void Nibbler::changePlayer(Map_Element player)
{
    int tmp_y = 0;
    int tmp_x = 0;

    for (auto &n : _map) {
        if (tmp_y == _snake[0].first) {
            for (auto &n2 : n) {
                if (tmp_x == _snake[0].second)
                    n2 = player;
                tmp_x++;
            }
        }
        tmp_y++;
    }
}

Map_Element Nibbler::getMap_Elem(int y, int x)
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
    return (ITEM2);
}

void Nibbler::makeAction(Events event)
{
    Map_Element play = getMap_Elem(_snake[0].first, _snake[0].second);

    if ((event == RIGHT && play == PLAYER_HEAD_LEFT) || (event == LEFT && play == PLAYER_HEAD_RIGHT)) {
        changePlayer(PLAYER_HEAD_UP);
    } else if ((event == LEFT && play == PLAYER_HEAD_LEFT) || (event == RIGHT && play == PLAYER_HEAD_RIGHT)) {
        changePlayer(PLAYER_HEAD_DOWN);
    } else if ((event == RIGHT && play == PLAYER_HEAD_DOWN) || (event == LEFT && play == PLAYER_HEAD_UP)) {
        changePlayer(PLAYER_HEAD_LEFT);
    } else if ((event == RIGHT && play == PLAYER_HEAD_UP) || (event == LEFT && play == PLAYER_HEAD_DOWN)) {
        changePlayer(PLAYER_HEAD_RIGHT);
    } else if (event == UP) {
        change_frame_rate();
    } else if (event == DOWN) {
        _frame += 0.010;
    }

}

std::map<Map_Element, std::string> Nibbler::getAssets()
{
    return (_list);
}

bool Nibbler::isEnd()
{
    return (_isEnd);
}

extern "C" std::shared_ptr<IGames> gameEntrypoint()
{
    return std::shared_ptr<IGames>(new Nibbler());
}
