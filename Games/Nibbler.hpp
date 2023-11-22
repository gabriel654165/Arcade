/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** SpaceInvaders
*/

#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include "../Arcade.hpp"
#include "IGames.hpp"
#include <chrono>

class Nibbler : public IGames {
public:
    Nibbler();
    ~Nibbler();
    void update() override;
    void reset() override;
    int getScore() override;
    std::list<std::list<Map_Element>> getMap() override;
    void makeAction(Events event) override;
    std::map<Map_Element, std::string> getAssets() override;
    bool isEnd() override;
private:
    std::list<std::list<Map_Element>> _map;
    int score;
    bool _isEnd;
    double _frame;
    std::map<Map_Element, std::string> _list;
    std::vector<std::pair<int, int>> _snake;

    std::chrono::_V2::system_clock::time_point _timer;
    std::chrono::_V2::system_clock::time_point _timer_fruit;

    void changePlayer(Map_Element player);
    std::pair<int, int> getPlayer_pos();
    Map_Element getMap_Elem(int y, int x);
    void mooveHead(int y, int x);
    void mooveSnake();
    void selectDirection();
    void changeMap(int y, int x, Map_Element elem);
    void clear_snake_on_Map();
    void add_snake_on_Map(Map_Element head);
    void loadMap(std::string filename);
    void generateFruit_on_map();
    std::pair<int, int> check_around(std::pair<int, int> tmp);
    void change_frame_rate();
    void change_score(Map_Element elem);
    std::pair<int, int> getItem_pos();

};

#endif /* !SPACE_INVADERS_HPP_ */