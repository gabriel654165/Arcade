/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-thomas1.tricaud
** File description:
** Arcade
*/

#ifndef ARCADE_HPP_
#define ARCADE_HPP_

#include <list>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <string.h>
#include <dlfcn.h>
#include <functional>
#include <filesystem>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
#include <unordered_map>
#include <fstream>

#include <ncurses.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Glyph.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <SFML/Graphics/View.hpp>

enum Game_State
{
    USERNAME,
    MENU,
    GAME,
    PAUSE,
    END
};

enum Events
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    PREV_DISPLAY,
    NEXT_DISPLAY,
    PREV_GAME,
    NEXT_GAME,
    RESTART,
    BACK_MENU,
    MAKE_PAUSE,
    EXIT,
    VALIDATION,
    NONE
};

enum Selected_Field
{
    GAMES,
    DISPLAYS
};

enum Map_Element
{
    VOID,
    PLAYER_HEAD_UP,
    PLAYER_HEAD_DOWN,
    PLAYER_HEAD_LEFT,
    PLAYER_HEAD_RIGHT,
    PLAYER_BODY,
    PLAYER_END,
    ENEMY,
    WALL,
    ITEM1,
    ITEM2,
    ENEMY_VULNERABLE
};

enum Ghost_dir
{
    G_RIGHT,
    G_LEFT,
    G_UP,
    G_DOWN,
    G_NONE
};

#endif /* !ARCADE_HPP_ */
