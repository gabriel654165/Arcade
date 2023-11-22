//
// Created by gabriel on 12/13/4021.
//

#ifndef NCURSELIB_HPP
#define NCURSELIB_HPP

#include "IDisplay.hpp"


class Ncurse : public IDisplay {
public:
    Ncurse();
    ~Ncurse();
    //void init() override;
    void displayMenu(std::list<std::pair<std::string, bool>>,
                     std::list<std::pair<std::string, bool>>, Selected_Field) override;
    void displayMap(std::list<std::list<Map_Element>>) override;
    void displayScore(int) override;
    void displayBestScores(std::list<std::string>) override;
    void displayUserName(std::string) override;
    void displayEnd() override;
    void userNameSelection() override;
    Events getLastInput() override;
    void setAssets(std::map<Map_Element, std::string>) override;
    std::string getUsername() override;
private:
    std::string _username;
    WINDOW *_mainwin;
    bool _isEnd;
    Game_State _state;
    //Event _event;
    //Font _font;
    //Text _title;
    //RectangleShape _rect;
};

#endif /* !NCURSELIB_HPP */
