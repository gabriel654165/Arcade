/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** IGames
*/

#ifndef IGAMES_HPP_
#define IGAMES_HPP_

#include <list>
#include "../Arcade.hpp"
#include <map>
#include <string>

class IGames {
public:
    virtual ~IGames() = default;
    virtual void update() = 0;
    virtual void reset() = 0;
    virtual int getScore() = 0;
    virtual std::list<std::list<Map_Element>> getMap() = 0;
    virtual void makeAction(Events event) = 0;
    virtual std::map<Map_Element, std::string> getAssets() = 0;
    virtual bool isEnd() = 0;
};

#endif /* !IGAMES_HPP_ */
