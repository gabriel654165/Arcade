//
// Created by gabriel on 66/66/12.
//

#include "SDLlib.hpp"

SDLlib::SDLlib()
{
    _username = "";
    _isEnd = false;
    _state = USERNAME;
    // create window
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
        std::cerr << "Failed to initialize the SDL2 library : " << SDL_GetError() << std::endl;
    _window = SDL_CreateWindow("arcade",0, 0, 1920, 1080, 0);
    if (!_window)
        std::cerr << "Failed to create window : " << SDL_GetError() << std::endl;
    _renderer = SDL_CreateRenderer(_window , -1, 0);
    if (!_renderer)
        std::cerr << "Failed to get the renderer from the window : " << SDL_GetError() << std::endl;
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    Arialfont = TTF_OpenFont("Utility/font/Group1/arial.ttf", 24);
    BigArialfont = TTF_OpenFont("Utility/font/Group1/arial.ttf", 30);
    Boldfont = TTF_OpenFont("Utility/font/Group1/Bold.otf", 24);
    WhiteColor = {255, 255, 255};
    GreenColor = {0, 255, 0};
    BlueColor = {0, 0, 255};
    RedColor = {255, 0, 0};
}

SDLlib::~SDLlib()
{
    for (auto &it : _assets)
        SDL_DestroyTexture(it.second);
    IMG_Quit();
    TTF_CloseFont(Arialfont);
    TTF_CloseFont(Boldfont);
    TTF_CloseFont(BigArialfont);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_Quit();
    SDL_Quit();
}

std::string SDLlib::getUsername()
{
    return _username;
}

void SDLlib::putText(const std::string message, int posX, int posY, SDL_Color color, TTF_Font *font)
{
    int w = 0;
    int h = 0;

    _window_surface = TTF_RenderText_Solid(font, message.c_str(), color);
    texture = SDL_CreateTextureFromSurface(_renderer, _window_surface);
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect Message_rect;
    Message_rect.x = posX;
    Message_rect.y = posY;
    Message_rect.w = w;
    Message_rect.h = h;
    SDL_RenderCopy(_renderer, texture, NULL, &Message_rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(_window_surface);
}

void SDLlib::userNameSelection()
{
    putText("Enter your name : ", 880, 420, GreenColor, Arialfont);
    putText(_username, 960 - (strlen(_username.c_str()) * 4), 520, WhiteColor, Arialfont);
    SDL_RenderPresent(_renderer);
}

void SDLlib::displayMenu(std::list<std::pair<std::string, bool>> display,
                         std::list<std::pair<std::string, bool>> game,
                         Selected_Field Field)
{
    _state = MENU;

    if (Field == GAMES) {
        putText("Games : ", 450, 350, GreenColor, BigArialfont);
        putText("Libs : ", 450, 500, BlueColor, Arialfont);
    } else if (Field == DISPLAYS) {
        putText("Games : ", 450, 350, BlueColor, Arialfont);
        putText("Libs : ", 450, 500, GreenColor, BigArialfont);
    }
    putText("Press ENTER to PLAY", 900, 750, BlueColor, Arialfont);
    for (auto &it : game)
        if (it.second)
            putText(std::string("< ") + it.first + std::string(" >"), 570, 350, WhiteColor, Arialfont);
    for (auto &it : display)
        if (it.second)
            putText(std::string("< ") + it.first + std::string(" >"), 570, 500, WhiteColor, Arialfont);
}

void SDLlib::displayBestScores(std::list <std::string> strBestScore)
{
    int line = 0;

    putText("1st : ", 1520, 350, BlueColor, BigArialfont);
    putText("2sd : ", 1520, 450, BlueColor, BigArialfont);
    putText("3th : ", 1520, 550, BlueColor, BigArialfont);
    for (auto &it : strBestScore) {
        putText(it, 1620, 350 + line, WhiteColor, BigArialfont);
        line += 100;
    }
    SDL_RenderPresent(_renderer);
}

void SDLlib::displayUserName(std::string name)
{
    putText("Name : ", 100, 350, BlueColor, BigArialfont);
    putText(name, 200, 350, WhiteColor, BigArialfont);
}

void SDLlib::displayScore(int score)
{
    putText("Score : ", 100, 450, BlueColor, BigArialfont);
    putText(std::to_string(score), 200, 450, WhiteColor, BigArialfont);
}

void SDLlib::displayImage(int posX, int posY, int w, int h, SDL_Texture *texture)
{
    SDL_Rect Image_rect;
    Image_rect.x = posX;
    Image_rect.y = posY;
    Image_rect.w = w;
    Image_rect.h = h;
    SDL_RenderCopy(_renderer, texture, NULL, &Image_rect);
}

void SDLlib::displayMap(std::list <std::list<Map_Element>> map)
{
    int start_x = 550;
    int start_y = 100;
    int x = start_x;
    int y = start_y;
    int w = 30;
    int h = 30;
    _state = GAME;

    for (auto &n : map) {
        for (auto &n2 : n) {
            displayImage(x, y, w, h, _assets[n2]);
            x += w;
        }
        x = start_x;
        y += h;
    }
}

void SDLlib::setAssets(std::map <Map_Element, std::string> asset)
{
    for (auto it : asset)
        _assets[it.first] = IMG_LoadTexture(_renderer, it.second.c_str());
}

Events SDLlib::getLastInput()
{
    SDL_RenderClear(_renderer);

    if (SDL_PollEvent(&_eventList) > 0) {
        if (_state == USERNAME) {
            switch (_eventList.type) {
                case SDL_TEXTINPUT:
                    if (_state == USERNAME && _username.size() < 15) {
                        _username.append(_eventList.text.text);
                        break;
                    }
            }
        }

        switch (_eventList.type) {
            case SDL_QUIT:
                return Events::EXIT;
            case SDL_KEYDOWN:
                if (_eventList.key.keysym.scancode == SDL_SCANCODE_UP)
                    return Events::UP;
                if (_eventList.key.keysym.scancode == SDL_SCANCODE_DOWN)
                    return Events::DOWN;
                if (_eventList.key.keysym.scancode == SDL_SCANCODE_LEFT)
                    return Events::LEFT;
                if (_eventList.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                    return Events::RIGHT;
                if (_eventList.key.keysym.scancode == SDL_SCANCODE_F1)
                    return Events::PREV_DISPLAY;
                if (_eventList.key.keysym.scancode == SDL_SCANCODE_F2)
                    return Events::NEXT_DISPLAY;
                if (_eventList.key.keysym.scancode == SDL_SCANCODE_F3)
                    return Events::PREV_GAME;
                if (_eventList.key.keysym.scancode == SDL_SCANCODE_F4)
                    return Events::NEXT_GAME;
                if (_eventList.key.keysym.scancode == SDL_SCANCODE_RETURN)
                    return Events::VALIDATION;
                if (_state == USERNAME && _username.size() > 0 && _eventList.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
                    _username.pop_back();
                if (_eventList.key.keysym.scancode == SDL_SCANCODE_P)
                    return Events::MAKE_PAUSE;
                if (_eventList.key.keysym.scancode == SDL_SCANCODE_R)
                    return Events::RESTART;
                if (_eventList.key.keysym.scancode == SDL_SCANCODE_E)
                    return Events::BACK_MENU;
                if (_eventList.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    return Events::EXIT;
            default:
                return Events::NONE;

        }
    }
    return Events::NONE;
}

void SDLlib::displayEnd()
{
    SDL_RenderClear(_renderer);
    putText("GAME OVER", 880, 420, RedColor, BigArialfont);
    putText("Restart [r]", 892, 520, WhiteColor, Arialfont);
    putText("Back to Menu [escp]", 850, 580, WhiteColor, Arialfont);
    SDL_RenderPresent(_renderer);
}

extern "C" std::shared_ptr<IDisplay> displayEntrypoint()
{
    return std::shared_ptr<IDisplay>(new SDLlib());
}