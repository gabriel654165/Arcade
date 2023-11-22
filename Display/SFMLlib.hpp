//
// Created by thomas on 24/03/2021.
//

#ifndef B_OOP_400_PAR_4_1_ARCADE_BALTHAZAR_ROQUE_SFMLLIB_HPP
#define B_OOP_400_PAR_4_1_ARCADE_BALTHAZAR_ROQUE_SFMLLIB_HPP

#include "IDisplay.hpp"


class SFMLlib : public IDisplay {
public:
    SFMLlib();
    ~SFMLlib();
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
    void drawRect(Selected_Field);
    void eventUsername();
    void displayEndGame();

private:
    std::unordered_map<Map_Element, sf::Texture> _asset;
    sf::Sprite _sprite;
    sf::Event _event;
    sf::Font _font;
    sf::RenderWindow _window;
    sf::Text _title;
    sf::RectangleShape _rect;
    std::string _username;
    bool _isEnd;
    Game_State _state;
};


#endif //B_OOP_400_PAR_4_1_ARCADE_BALTHAZAR_ROQUE_SFMLLIB_HPP
