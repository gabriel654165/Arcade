/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "../Arcade.hpp"
#include "IGames.hpp"

class Pacman : public IGames {
public:
    Pacman();
    ~Pacman();
    void update() override;
    void reset() override;
    int getScore() override;
    std::list<std::list<Map_Element>> getMap() override;
    void makeAction(Events event) override;
    std::map<Map_Element, std::string> getAssets() override;
    bool isEnd() override;
    
private:
    std::list<std::list<Map_Element>> _map;
    std::list<std::pair<Map_Element, std::pair<int, int>>> _saveObj;
    std::vector<std::vector<Map_Element>> _mapVector;
    std::chrono::_V2::system_clock::time_point _timer;
    int score;
    bool _isGod;
    int _posx;
    int _posy;
    bool vulnerable;
    bool _isEnd;
    std::vector<std::pair<std::pair<Ghost_dir, bool>, std::pair<int, int>>> ghost_handling;
    std::map<Map_Element, std::string> _list;
    std::vector<std::pair<int, int>> _ghostPosition;

    void changePlayer(Map_Element player);
    void loadMap(std::string filename);
    void loadMapVector();
    void setMaptoMapVector();
    Map_Element getMap_Elem(int y, int x);
    void moovePlayer();
    void refactoMovePLayer(int y, int x, Map_Element player);
    void moveGhost();
    bool exceptionMove(int);
    std::pair<int, int> chooseDirection(std::pair<int, int> pos);
    void setPlayer_pos();
    void beginTheCourse();
    bool refactoMoveGhostRight(int);
    bool refactoMoveGhostLeft(int);
    bool refactoMoveGhostUp(int);
    bool refactoMoveGhostDown(int);
    bool gotIntersection(int);
    void randomDir(int);
    Map_Element getSaveObj(int, int);
    bool exceptCase(int);
    void fearGhost();
    void resetGhost(int, int);
    void unfearGhost();
    void ghostWaitingRoom();
};

#endif /* !IPACMAN_HPP_ */
