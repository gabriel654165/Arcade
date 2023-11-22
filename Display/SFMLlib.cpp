//
// Created by thomas on 24/03/2021.
//

#include "SFMLlib.hpp"

SFMLlib::SFMLlib()
{
    _state = USERNAME;
    _username = "";
    _window.create({sf::VideoMode::getDesktopMode().width,
                    sf::VideoMode::getDesktopMode().height},
                   "arcade");
    _font.loadFromFile("Utility/font/Group1/arial.ttf");
    _title.setFont(_font);
    sf::Color color(0, 0, 238, 255);
    _title.setOutlineColor(color);
    _title.setOutlineThickness(5);
    _title.setFillColor(sf::Color::Cyan);
    _title.setCharacterSize(50);
    _rect.setSize({230, 60});
    _rect.setFillColor(sf::Color(255, 255, 255, 100));
    _isEnd = false;
}

SFMLlib::~SFMLlib()
{
    _window.close();
}

void SFMLlib::eventUsername()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && _username.size() > 0)
        _username = _username.substr(0, _username.size() - 1);
    if (_event.type == sf::Event::TextEntered && _username.size() < 15)
        _username += _event.text.unicode;
}

Events SFMLlib::getLastInput()
{
    while (_window.pollEvent(_event)) {
        if (_state == USERNAME) {
            eventUsername();
        }
        if (_event.type == sf::Event::KeyPressed) {
            if (_event.key.code == sf::Keyboard::Key::Up)
                    return Events::UP;
            if (_event.key.code == sf::Keyboard::Key::Down)
                return Events::DOWN;
            if (_event.key.code == sf::Keyboard::Key::Left)
                return Events::LEFT;
            if (_event.key.code == sf::Keyboard::Key::Right)
                return Events::RIGHT;
            if (_event.key.code == sf::Keyboard::Key::F1)
                return Events::PREV_DISPLAY;
            if (_event.key.code == sf::Keyboard::Key::F2)
                return Events::NEXT_DISPLAY;
            if (_event.key.code == sf::Keyboard::Key::F3)
                return Events::PREV_GAME;
            if (_event.key.code == sf::Keyboard::Key::F4)
                return Events::NEXT_GAME;
            if (_event.key.code == sf::Keyboard::Key::Escape)
                return Events::EXIT;
            if (_event.key.code == sf::Keyboard::Key::Enter)
                return Events::VALIDATION;
            if (_event.key.code == sf::Keyboard::Key::R) {
                _isEnd = false;
                return Events::RESTART;
            }
            if (_event.key.code == sf::Keyboard::Key::P)
                return Events::MAKE_PAUSE;
            if (_event.key.code == sf::Keyboard::Key::E)
                return Events::BACK_MENU;
        }
        if (_event.type == sf::Event::KeyReleased) {
            return Events::NONE;
        }
    }
    return Events::NONE;
}


void SFMLlib::drawRect(Selected_Field field)
{
    if (field == GAMES) {
        _rect.setPosition({200, 300});
        _window.draw(_rect);
    }
    else if (field == DISPLAYS) {
        _rect.setPosition({200, 500});
        _window.draw(_rect);
    }

}

void SFMLlib::displayMenu(std::list<std::pair<std::string, bool>> display,
                          std::list<std::pair<std::string, bool>> game,
                          Selected_Field field)
{
    _window.clear();
    _state = MENU;

    _title.setString("GAME : ");
    _title.setPosition({200, 300});
    _window.draw(_title);
    for (auto &it : game) {
        if (it.second) {
            _title.setString(it.first);
        }
    }
    _title.setPosition({500, 300});
    _window.draw(_title);

    _title.setString("LIBRAIRIE : ");
    _title.setPosition({200, 500});
    _window.draw(_title);
    for (auto &it : display) {
        if (it.second) {
            _title.setString(it.first);
        }
    }
    _title.setPosition({500, 500});
    _window.draw(_title);

    _title.setString("Press ENTER to PLAY");
    _title.setPosition({750, 700});
    _window.draw(_title);
    drawRect(field);
}

std::string SFMLlib::getUsername()
{
    return _username;
}

void SFMLlib::displayEndGame()
{
    _window.clear();
    _title.setString("YOU LOSE!");
    _title.setCharacterSize(100);
    _title.setPosition({750, 300});
    _window.draw(_title);
    _title.setString("press R to restart");
    _title.setCharacterSize(60);
    _title.setPosition({730, 500});
    _window.draw(_title);
    _title.setString("press ESC to back to menu");
    _title.setPosition({630, 700});
    _window.draw(_title);
    _window.display();
}

void SFMLlib::displayMap(std::list <std::list<Map_Element>> map)
{
    _state = GAME;
    int x, y = 0;
    int beginX = _window.getSize().x / 2 - _window.getSize().x / 4;
    int sizeX = (_window.getSize().x / 2) / map.begin()->size();
    int sizeY = (_window.getSize().y / 2) / map.size();
    int beginY = _window.getSize().y / 2 - (sizeX * map.size() / 2);
    sf::IntRect rect(0, 0, _window.mapPixelToCoords({sizeX, sizeY}).x, _window.mapPixelToCoords({sizeX, sizeY}).x);
    for (auto &it: map) {
        x = 0;
        for (auto &ite: it) {
            if (ite == WALL || ite == VOID) {
                _sprite.setTextureRect(rect);
                _sprite.setScale({1, 1});
            }
            else {
                _sprite.setTextureRect({0, 0, static_cast<int>(_asset[ite].getSize().x), static_cast<int>(_asset[ite].getSize().y)});
                _sprite.setScale({0.8, 0.8});
            }
            _sprite.setTexture(_asset[ite]);
            _sprite.setPosition(_window.mapPixelToCoords({beginX + x * sizeX, beginY + y * sizeX}));
            _window.draw(_sprite);
            x++;
        }
        y++;
    }
}

void SFMLlib::displayBestScores(std::list <std::string> strBestScore)
{
    float line = 0;

    _title.setString("1st : ");
    _title.setPosition({1450, 350});
    _window.draw(_title);
    _title.setString("2sd : ");
    _title.setPosition({1450, 450});
    _window.draw(_title);
    _title.setString("3th : ");
    _title.setPosition({1450, 550});
    _window.draw(_title);
    for (auto &it : strBestScore) {
        _title.setString(it);
        _title.setPosition({1600, 350 + line});
        _window.draw(_title);
        line += 100;
    }
    _window.display();
}

void SFMLlib::displayUserName(std::string name)
{
    sf::Color color(0, 0, 238, 255);
    _window.clear();
    _title.setCharacterSize(50);
    _title.setString("PLAYER : ");
    _title.setFillColor(sf::Color::Yellow);
    _title.setOutlineColor(color);
    _title.setOutlineThickness(5);
    _title.setPosition({50, 500});
    _window.draw(_title);
    _title.setString(name);
    _title.setPosition({260, 500});
    _window.draw(_title);
}

void SFMLlib::displayScore(int score)
{
    _title.setString("SCORE : ");
    _title.setPosition({50, 350});
    _window.draw(_title);
    _title.setString(std::to_string(score));
    _title.setPosition({250, 350});
    _window.draw(_title);
}

void SFMLlib::setAssets(std::map <Map_Element, std::string> asset)
{
    for (auto it : asset) {
        _asset[it.first].loadFromFile(it.second, sf::IntRect());
    }
}

void SFMLlib::userNameSelection()
{
    _window.clear();
    _title.setString("Enter your Name");
    _title.setPosition(_window.mapPixelToCoords({static_cast<int>(_window.getSize().x / 2 - (_title.getCharacterSize() * 7.5 / 2)),
                                                 static_cast<int>(_window.getSize().y / 2 - 100)}));
    _window.draw(_title);
    _title.setString(_username);
    _title.setPosition(_window.mapPixelToCoords({static_cast<int>((_window.getSize().x / 2) - ((_username.size()) * 12) - 10),
                                                 static_cast<int>(_window.getSize().y / 2)}));
    _window.draw(_title);
    _window.display();

}

void SFMLlib::displayEnd()
{
    _isEnd = true;
    displayEndGame();
}


extern "C" std::shared_ptr<IDisplay> displayEntrypoint()
{
    return std::shared_ptr<IDisplay>(new SFMLlib());
}