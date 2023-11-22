/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** DlManager
*/

#ifndef DLMANAGER_HPP_
#define DLMANAGER_HPP_

#include "../Display/IDisplay.hpp"
#include "../Games/IGames.hpp"
#include "../Arcade.hpp"

class DlManager {
public:
    DlManager();
    ~DlManager();

    void *openSelectedList(const char *filename, const char *entryPoint);
    bool isOpenAble(const char *filename,const char *entryPoint);
    void removeHandlerGame();
    void removeHandlerLibs();
private:
    std::list<void *> _handleListLibs;
    std::list<void *> _handleListGame;
};

#endif /* !DLMANAGER_HPP_ */