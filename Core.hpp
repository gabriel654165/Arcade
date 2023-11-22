/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Core
*/

#ifndef Core_HPP_
#define Core_HPP_

#include "Games/IGames.hpp"
#include "Display/IDisplay.hpp"
#include "DlManager/DlManager.hpp"
#include "Arcade.hpp"

class Core {
public:
    Core(DlManager *dlManager);
    ~Core();

    void loadDisplayLib(const std::string &filename);
    void loadGameLib(const std::string &filename);
    std::shared_ptr<IDisplay> _display;
    std::shared_ptr<IGames> _game;
    std::list<std::pair<std::string, bool>> _gameList;
    std::list<std::pair<std::string, bool>> _displayList;
    void gameLoop();
private:
    void manageMenuSelectedField(Events key);
    void manageSelection(Events key);
    void switchLibSelection(Events key);
    void switchGameSelection(Events key);
    void manageMenuSelection(Events key);
    void manageEvents(Events key);
    void changeGame();
    void changeDisplay();
    void getHighscores();
    void setHightScore(int score);
    void getSelectedField();

    DlManager *_dl;
    std::list<std::pair<std::string, bool>> _buttonList;
    std::string _username;
    Game_State _state;
    Selected_Field _selectField;
    std::list<std::string> _highScores;
    bool _close;
};


#endif /* !Core_HPP_ */