/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Core
*/

#include "prototypes.hpp"

Core::Core(DlManager *dlManager)
{
    _dl = dlManager;
    _buttonList = {{"game", true}, {"lib", false}};
    _state = USERNAME;
    _close = false;
    _selectField = GAMES;
}

Core::~Core()
{
}

void Core::gameLoop()
{
    getHighscores();
    while (!_close)
    {
        manageEvents(_display->getLastInput());
        if (_state == MENU) {
            _display->displayMenu(_displayList, _gameList, _selectField);
            _display->displayBestScores(_highScores);
        } else if (_state == USERNAME) {
            _display->userNameSelection();
        } else if (_state == GAME) {
            _game->update();
            _display->displayUserName(_username);
            _display->displayScore(_game->getScore());
            _display->displayMap(_game->getMap());
            _display->displayBestScores(_highScores);
        }
        if (_state == END) {
            _display->displayEnd();
        }
    }
}

void Core::getHighscores()
{
    std::string line;
    std::ifstream f("Utility/Score/score.txt");

    _highScores.erase(_highScores.begin(), _highScores.end());
    if (f.is_open()) {
        for (int cpt = 0; getline(f, line) && cpt != 3; ++cpt) {
            _highScores.push_back(line);
        }
        f.close();
    } else
        std::cerr << "No such file or directory" << "Utility/Score/score.txt" << std::endl;
}

void Core::setHightScore(int score)
{
    std::string line;
    std::string firstline;
    std::string secondline;
    std::string thirdline;
    std::string firstlineScore;
    std::string secondlineScore;
    std::string thirdlineScore;

    std::ifstream f1("Utility/Score/score.txt");
    if (f1.is_open()) {
        for (int cpt = 0; getline(f1, line) && cpt != 3; ++cpt) {
            if (cpt == 0)
                firstline = line;
            if (cpt == 1)
                secondline = line;
            if (cpt == 2)
                thirdline = line;

            auto iteLine = line.find_last_of(" ");
            line.erase(0, iteLine + 1);

            if (cpt == 0) {
                firstlineScore = line;
            } else if (cpt == 1) {
                secondlineScore = line;
            } else if (cpt == 2) {
                thirdlineScore = line;
            }
        }
        f1.close();
    }
    //rewrite lines + score
    std::ofstream f("Utility/Score/score.txt");
    if (f.is_open()) {
        if (std::atoi(firstlineScore.c_str()) < score) {
            firstlineScore = std::to_string(score);
            f << _username + " " + firstlineScore << std::endl;
            f << secondline << std::endl;
            f << thirdline;
        } else if (std::atoi(secondlineScore.c_str()) < score) {
            secondlineScore = std::to_string(score);
            f << firstline << std::endl;
            f << _username + " " + secondlineScore << std::endl;
            f << thirdline;
        } else if (std::atoi(thirdlineScore.c_str()) < score) {
            thirdlineScore = std::to_string(score);
            f << firstline << std::endl;
            f << secondline << std::endl;
            f << _username + " " + thirdlineScore;
        } else {
            f << firstline << std::endl;
            f << secondline << std::endl;
            f << thirdline;
        }
        f.close();
    }
    getHighscores();
}

void Core::manageEvents(Events key)
{
    /* SWITCH GAME EVENTS */
    if (_state == MENU && key == VALIDATION) {
        changeDisplay();
        changeGame();
        _display->setAssets(_game->getAssets());
        _state = GAME;
    }
    if (_state == MENU && (key == UP || key == DOWN || key == LEFT || key == RIGHT))
        manageMenuSelection(key);

    if (key == NEXT_DISPLAY || key == PREV_DISPLAY) {
        switchLibSelection(key);
        changeDisplay();
        _display->setAssets(_game->getAssets());
    }
    if ((key == NEXT_GAME || key == PREV_GAME) && _state == GAME) {
        switchGameSelection(key);
        changeGame();
        _display->setAssets(_game->getAssets());
    }
    /* USERNAME FIRST SCREEN */
    if (_state == USERNAME && key == VALIDATION && _display->getUsername().size() > 0) {
        _username = _display->getUsername();
        _state = MENU;
    }
    /* BUTTONS IN GAME */
    if ((_state == GAME || _state == PAUSE || _state == END) && key == BACK_MENU) {
        _state = MENU;
        _game->reset();
    }
    if ((_state == GAME || _state == PAUSE || _state == END) && key == RESTART) {
        _state = GAME;
        _game->reset();
    }
    static int i = 0;
    i++;
    if (_state == GAME && key == MAKE_PAUSE)
        _state = PAUSE;
    else if (_state == PAUSE && key == MAKE_PAUSE)
        _state = GAME;

    if (_state == GAME && (key == UP || key == DOWN || key == LEFT || key == RIGHT))
        _game->makeAction(key);
    if (_state != END && _game->isEnd()) {
        setHightScore(_game->getScore());
        _state = END;
    }
    if (key == EXIT && _state != USERNAME) {
        _close = true;
    }
}

void Core::loadDisplayLib(const std::string &filename)
{
    static int start = 0;
    std::shared_ptr<IDisplay>(*entrypoint)() = (typeof(entrypoint))_dl->openSelectedList(filename.c_str(), "displayEntrypoint");

    if (start == 0) {
        ++start;
        std::pair<std::string, bool> myPair;
        myPair.first = filename;
        myPair.second = true;
        _displayList.push_front(myPair);
    } else
        _display = nullptr;
    _display = entrypoint();
}

void Core::loadGameLib(const std::string &filename)
{
    static int start = 0;
    std::shared_ptr<IGames>(*entrypoint)() = (typeof(entrypoint))_dl->openSelectedList(filename.c_str(), "gameEntrypoint");

    if (start == 0) {
        ++start;
        std::pair<std::string, bool> myPair;
        myPair.first = filename;
        myPair.second = true;
        _gameList.push_front(myPair);
    } else
        _game = nullptr;
    _game = entrypoint();
}

void Core::changeGame()
{
    for (auto &n : _gameList)
        if (n.second)
            loadGameLib(n.first);
}

void Core::changeDisplay()
{
    for (auto &n : _displayList) {
        if (n.second)
            loadDisplayLib(n.first);
    }
}

void Core::manageMenuSelection(Events key)
{
    manageMenuSelectedField(key);
    manageSelection(key);
}

void Core::manageMenuSelectedField(Events key)
{
    bool isTrue = false;
    if (key == DOWN) {
        for (auto it = _buttonList.begin(); it != _buttonList.end(); ++it) {
            if (it->second) {
                isTrue = it->second;
                it->second = false;
            } else if (isTrue) {
                it->second = isTrue;
                isTrue = false;
            }
        }
        if (isTrue)
            _buttonList.begin()->second = true;
    }
    isTrue = false;
    if (key == UP) {
        for (auto it = _buttonList.rbegin(); it != _buttonList.rend(); ++it) {
            if (it->second) {
                isTrue = it->second;
                it->second = false;
            } else if (isTrue) {
                it->second = isTrue;
                isTrue = false;
            }
        }
        if (isTrue)
            _buttonList.rbegin()->second = true;
    }
}

void Core::switchGameSelection(Events key)
{
    bool isTrue = false;
    if (_gameList.size() > 1 && (key == RIGHT || key == NEXT_GAME)) {
        for (auto it = _gameList.begin(); it != _gameList.end(); it++) {
            if (it != _gameList.end() && it->second && !isTrue) {
                isTrue = it->second;
                it->second = false;
            } else if (isTrue) {
                it->second = isTrue;
                isTrue = false;
            }
        }
        if (isTrue)
            _gameList.begin()->second = true;
    }
    isTrue = false;
    if (_gameList.size() > 1 && (key == LEFT || key == PREV_GAME)) {
        for (auto it = _gameList.rbegin(); it != _gameList.rend(); ++it) {
            if (it->second) {
                isTrue = it->second;
                it->second = false;
            } else if (isTrue) {
                it->second = isTrue;
                isTrue = false;
            }
        if (isTrue)
            _gameList.rbegin()->second = true;}
    }
}

void Core::switchLibSelection(Events key)
{
    bool isTrue = false;
    if ((key == RIGHT || key == NEXT_DISPLAY) && _displayList.size() > 1) {
        for (auto it = _displayList.begin(); it != _displayList.end(); ++it) {
            if (it->second) {
                isTrue = it->second;
                it->second = false;
            } else if (isTrue) {
                it->second = isTrue;
                isTrue = false;
            }
        }
        if (isTrue)
            _displayList.begin()->second = true;
    }
    isTrue = false;
    if ((key == LEFT || key == PREV_DISPLAY) && _displayList.size() > 1) {
        for (auto it = _displayList.rbegin(); it != _displayList.rend(); ++it) {
            if (it->second) {
                isTrue = it->second;
                it->second = false;
            } else if (isTrue) {
                it->second = isTrue;
                isTrue = false;
            }
        }
        if (isTrue)
            _displayList.rbegin()->second = true;
    }
}

void Core::getSelectedField()
{
    for (auto it = _buttonList.begin(); it != _buttonList.end(); it++) {
        if (it->second && it->first == "game")
            _selectField = GAMES;
        if (it->second && it->first == "lib")
            _selectField = DISPLAYS;
    }
}

void Core::manageSelection(Events key)
{
    for (auto it = _buttonList.begin(); it != _buttonList.end(); it++) {
        if (it->second && it->first == "game") {
            switchGameSelection(key);
        }
        else if (it->second && it->first == "lib") {
            switchLibSelection(key);
        }
    }
    getSelectedField();
}
