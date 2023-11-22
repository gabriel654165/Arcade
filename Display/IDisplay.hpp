/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-thomas1.tricaud
** File description:
** IDisplay
*/

#ifndef IDisplay_HPP_
#define IDisplay_HPP_

#include <iostream>
#include <list>
#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../Arcade.hpp"

class IDisplay {
public:
    virtual ~IDisplay() = default;
    virtual void displayMenu(std::list<std::pair<std::string, bool>>,
                             std::list<std::pair<std::string, bool>>, Selected_Field) = 0;
    virtual void displayMap(std::list<std::list<Map_Element>>) = 0;
    virtual void displayScore(int) = 0;
    virtual void displayBestScores(std::list<std::string>) = 0;
    virtual void displayUserName(std::string) = 0;
    virtual void displayEnd() = 0;
    virtual void userNameSelection() = 0;
    virtual Events getLastInput() = 0;
    virtual void setAssets(std::map<Map_Element, std::string>) = 0;
    virtual std::string getUsername() = 0;
};

#endif /* !IDisplay_HPP_ */
