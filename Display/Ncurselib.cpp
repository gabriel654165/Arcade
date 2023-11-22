//
// Created by gabriel on 66/66/12.
//

#include "Ncurselib.hpp"

Ncurse::Ncurse()
{
    if ((this->_mainwin = initscr()) == NULL) {
        fprintf(stderr, "Error initialising ncurses.\n");
        return;
    }
    noecho();
    keypad(this->_mainwin, TRUE);
    start_color();
    nodelay(this->_mainwin, TRUE);
    curs_set(FALSE);
    _isEnd = false;
    _state = USERNAME;
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLUE);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_GREEN, COLOR_BLACK);
}

Ncurse::~Ncurse()
{
    //delwin(this->_mainwin);
    refresh();
    //wclear(stdscr);
    clear();
    endwin();
}

void Ncurse::displayMenu(std::list<std::pair<std::string, bool>> display,
                         std::list<std::pair<std::string, bool>> game,
                         Selected_Field Field)
{
    int x = 0;
    int y = 0;

    _state = MENU;
    getmaxyx(this->_mainwin, x, y);
    box(this->_mainwin, 0, 0);

    attron(COLOR_PAIR(3));
    mvwaddstr(this->_mainwin, (x / 3) + 5, (y / 3) - 10, "Games : ");
    mvwaddstr(this->_mainwin, (x / 3) + 10, (y / 3) - 10, "Libs : ");
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(1));
    mvwaddstr(this->_mainwin, (x / 2) + 14, (y / 2) - 8, "                       ");
    mvwaddstr(this->_mainwin, (x / 2) + 15, (y / 2) - 8, "  Press ENTER to PLAY  ");
    mvwaddstr(this->_mainwin, (x / 2) + 16, (y / 2) - 8, "                       ");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    if (Field == GAMES) {
        mvwaddstr(this->_mainwin, (x / 3) + 5, (y / 3) - 10, "Games : ");
    } else if (Field == DISPLAYS) {
        mvwaddstr(this->_mainwin, (x / 3) + 10, (y / 3) - 10, "Libs : ");
    }
    attroff(COLOR_PAIR(2));
    for (auto &it : game)
        if (it.second)
            mvwaddstr(this->_mainwin, (x / 3) + 5, (y / 3), ("< " + it.first + " >").c_str());
    for (auto &it : display)
        if (it.second)
            mvwaddstr(this->_mainwin, (x / 3) + 10, (y / 3), ("< " + it.first + " >").c_str());
}

void Ncurse::displayBestScores(std::list <std::string> strBestScore)
{
    int line = - 5;
    int x = 0;
    int y = 0;

    getmaxyx(this->_mainwin, y, x);
    attron(COLOR_PAIR(3));
    mvwaddstr(this->_mainwin, (y / 2) - 5, (x / 2) + (x / 3), "1st : ");
    mvwaddstr(this->_mainwin, (y / 2), (x / 2) + (x / 3), "2sd : ");
    mvwaddstr(this->_mainwin, (y / 2) + 5, (x / 2) + (x / 3), "3th : ");
    attroff(COLOR_PAIR(3));

    for (auto &it : strBestScore) {
        mvwaddstr(this->_mainwin, (y / 2) + line, (x / 2) + (x / 3) + 6, it.c_str());
        line += 5;
    }
    refresh();
}

void Ncurse::displayUserName(std::string name)
{
    int x = 0;
    int y = 0;

    getmaxyx(this->_mainwin, y, x);
    attron(COLOR_PAIR(3));
    mvwaddstr(this->_mainwin, (y / 2) - 5, (x / 2) - (x / 3) - (strlen("UserName : ")), "UserName : ");
    attroff(COLOR_PAIR(3));
    mvwaddstr(this->_mainwin, (y / 2) - 5, (x / 2) - (x / 3) - (strlen(name.c_str()) / 2), name.c_str());
}

void Ncurse::displayScore(int score)
{
    int x = 0;
    int y = 0;

    getmaxyx(this->_mainwin, y, x);
    attron(COLOR_PAIR(3));
    mvwaddstr(this->_mainwin, (y / 2) + 5, (x / 2) - (x / 3) - (strlen("Score : ")), "Score : ");
    attroff(COLOR_PAIR(3));
    mvwaddstr(this->_mainwin, (y / 2) + 5, (x / 2) - (x / 3), std::to_string(score).c_str());
}

void Ncurse::displayMap(std::list <std::list<Map_Element>> map)
{
    int x = 0;
    int y = 0;
    int cpt = 0;
    int cpt2 = 0;
    int size = map.size() + 25;

    _state = GAME;
    getmaxyx(this->_mainwin, y, x);
    for (auto &n : map) {
        for (auto &n2 : n) {
            if (n2 == WALL) {
                attron(COLOR_PAIR(4));
                mvwaddstr(this->_mainwin, (y / 5) + cpt, (x / 2) + cpt2 - size, "    ");
                mvwaddstr(this->_mainwin, (y / 5) + cpt + 1, (x / 2) + cpt2 - size, "    ");
                attroff(COLOR_PAIR(4));
            } else if (n2 == VOID)
                mvwaddstr(this->_mainwin, (y / 5) + cpt, (x / 2) + cpt2 - size, " ");
            else if (n2 == ITEM1) {
                attron(COLOR_PAIR(5));
                mvwaddstr(this->_mainwin, (y / 5) + cpt, (x / 2) + cpt2 - size, "    ");
                mvwaddstr(this->_mainwin, (y / 5) + cpt + 1, (x / 2) + cpt2 - size, " $$ ");
                attroff(COLOR_PAIR(5));
            } else if (n2 == ITEM2) {
                attron(COLOR_PAIR(6));
                mvwaddstr(this->_mainwin, (y / 5) + cpt, (x / 2) + cpt2 - size, "    ");
                mvwaddstr(this->_mainwin, (y / 5) + cpt + 1, (x / 2) + cpt2 - size, " $$ ");
                attroff(COLOR_PAIR(6));
            } else if (n2 == ENEMY) {
                attron(COLOR_PAIR(6));
                mvwaddstr(this->_mainwin, (y / 5) + cpt, (x / 2) + cpt2 - size, " __ ");
                mvwaddstr(this->_mainwin, (y / 5) + cpt + 1, (x / 2) + cpt2 - size, "(__)");
                attroff(COLOR_PAIR(6));
            }
            attron(COLOR_PAIR(5));
            if (n2 == PLAYER_HEAD_UP) {
                mvwaddstr(this->_mainwin, (y / 5) + cpt, (x / 2) + cpt2 - size, " \\/ ");
                mvwaddstr(this->_mainwin, (y / 5) + cpt + 1, (x / 2) + cpt2 - size, " \\/ ");
            } else if (n2 == PLAYER_HEAD_DOWN) {
                mvwaddstr(this->_mainwin, (y / 5) + cpt, (x / 2) + cpt2 - size, " /\\ ");
                mvwaddstr(this->_mainwin, (y / 5) + cpt + 1, (x / 2) + cpt2 - size, " /\\ ");
            } else if (n2 == PLAYER_HEAD_LEFT) {
                mvwaddstr(this->_mainwin, (y / 5) + cpt, (x / 2) + cpt2 - size, " \\\\ ");
                mvwaddstr(this->_mainwin, (y / 5) + cpt + 1, (x / 2) + cpt2 - size, " // ");
            } else if (n2 == PLAYER_HEAD_RIGHT) {
                mvwaddstr(this->_mainwin, (y / 5) + cpt, (x / 2) + cpt2 - size, " // ");
                mvwaddstr(this->_mainwin, (y / 5) + cpt + 1, (x / 2) + cpt2 - size, " \\\\ ");
            }
            if (n2 == PLAYER_BODY || n2 == PLAYER_END) {
                mvwaddstr(this->_mainwin, (y / 5) + cpt, (x / 2) + cpt2 - size, " oo ");
                mvwaddstr(this->_mainwin, (y / 5) + cpt + 1, (x / 2) + cpt2 - size, " oo ");
            }
            attroff(COLOR_PAIR(5));
            attron(COLOR_PAIR(7));
            if (n2 == ENEMY_VULNERABLE) {
                mvwaddstr(this->_mainwin, (y / 5) + cpt, (x / 2) + cpt2 - size, " __ ");
                mvwaddstr(this->_mainwin, (y / 5) + cpt + 1, (x / 2) + cpt2 - size, "(__)");
            }
            attroff(COLOR_PAIR(7));
            cpt2 += 4;
        }
        cpt2 = 0;
        cpt += 2;
    }
}

Events Ncurse::getLastInput()
{
    int a = wgetch(this->_mainwin);

    erase();
    if (_state == USERNAME) {
        if (a != ERR) {
            if (a == 263 && _username.size() != 0)
                _username.pop_back();
            else if (_username.size() < 15)
                _username.push_back(a);
        }
    }
    switch (a) {
        case KEY_UP:
            return Events::UP;
        case KEY_DOWN:
            return Events::DOWN;
        case KEY_RIGHT:
            return Events::RIGHT;
        case KEY_LEFT:
            return Events::LEFT;
        case KEY_F(1):
            return Events::PREV_DISPLAY;
        case KEY_F(2):
            return Events::NEXT_DISPLAY;
        case KEY_F(3):
            return Events::PREV_GAME;
        case KEY_F(4):
            return Events::NEXT_GAME;
        case '\n':
            return Events::VALIDATION;
        case KEY_ENTER:
            return Events::VALIDATION;
        case 'p':
            return Events::MAKE_PAUSE;
        case 'r':
            return Events::RESTART;
        case 'e':
            return Events::BACK_MENU;
        case KEY_CANCEL:
            return Events::EXIT;
        case KEY_CLOSE:
            return Events::EXIT;
        case 27:
            return Events::EXIT;
    }
    return Events::NONE;
}

void Ncurse::userNameSelection()
{
    int x = 0;
    int y = 0;

    getmaxyx(this->_mainwin, y, x);
    attron(COLOR_PAIR(2));
    mvwaddstr(this->_mainwin, (y / 2), (x / 2) - (strlen("Enter your Name : ") / 2), "Enter your Name : ");
    attroff(COLOR_PAIR(2));
    mvwaddstr(this->_mainwin, (y / 2) + 1, (x / 2) - (strlen(_username.c_str()) / 2), _username.c_str());
}

std::string Ncurse::getUsername()
{
    return _username;
}

void Ncurse::displayEnd() {
    int x, y;

    erase();
    getmaxyx(this->_mainwin, y, x);
    attron(COLOR_PAIR(3));
    mvwaddstr(this->_mainwin, (y / 2), (x / 2) - strlen("GAME OVER"), "GAME OVER");
    attroff(COLOR_PAIR(3));
    mvwaddstr(this->_mainwin, (y / 2) + 2, (x / 2) - 10, "Restart [r]");
    mvwaddstr(this->_mainwin, (y / 2) + 4, (x / 2) - 13, "Back to Menu [Escp]");
    _isEnd = false;
    refresh();
}

void Ncurse::setAssets(std::map <Map_Element, std::string>)
{
}

extern "C" std::shared_ptr<IDisplay> displayEntrypoint()
{
    return std::shared_ptr<IDisplay>(new Ncurse());
}