//
// Created by gabriel on 12/13/4021.
//

#ifndef SDL_HPP
#define SDL_HPP

#include "IDisplay.hpp"


class SDLlib : public IDisplay {
public:
    SDLlib();
    ~SDLlib();
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
    void putText(const std::string message, int posX, int posY, SDL_Color color, TTF_Font *font);
    void displayImage(int posX, int posY, int w, int h, SDL_Texture *texture);
private:
    std::unordered_map<Map_Element, SDL_Texture*> _assets;
    std::string _username;
    bool _isEnd;
    SDL_Window *_window;
    SDL_Surface *_window_surface;
    SDL_Renderer *_renderer;
    SDL_Event _eventList;

    SDL_Texture *texture;
    TTF_Font *Arialfont;
    TTF_Font *BigArialfont;
    TTF_Font *Boldfont;
    SDL_Color WhiteColor;
    SDL_Color GreenColor;
    SDL_Color BlueColor;
    SDL_Color RedColor;

    Game_State _state;
};

#endif /* !SDL_HPP */
