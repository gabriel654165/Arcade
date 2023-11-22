//
// Created by gabriel on 30/03/2021.
//

#include "prototypes.hpp"
#include "DlManager/DlManager.hpp"

void addIDisplaysToList(std::list<std::string> listIDisplay, Core *prog, DlManager *dl)
{
    std::pair<std::string, bool> myPair;

    for (auto &itr: listIDisplay) {
        if (dl->isOpenAble(itr.c_str(), strdup("displayEntrypoint"))
            && itr != prog->_displayList.begin()->first) {
            myPair.first = itr;
            myPair.second = false;
            prog->_displayList.push_back(myPair);
        }
    }
}

void addIGamesToList(std::list<std::string> listIGames, Core *prog, DlManager *dl)
{
    int start = 0;
    std::pair<std::string, bool> myPair;

    for (auto &itr: listIGames) {
        if (start == 0) {
            if (dl->isOpenAble(itr.c_str(), strdup("gameEntrypoint"))) {
                prog->loadGameLib(itr.c_str());
                ++start;
            }
        }
        if (dl->isOpenAble(itr.c_str(), strdup("gameEntrypoint"))
            && itr != prog->_gameList.begin()->first) {
            myPair.first = itr;
            myPair.second = false;
            prog->_gameList.push_back(myPair);
        }
    }
    if (start == 0)
        throw(std::invalid_argument("You need at least 1 Game to start Arcade"));
}

void addInterfacesToLists(Core *prog, DlManager *dl)
{
    std::list<std::string> listIDisplay {"./lib/arcade_ncurses.so", "./lib/arcade_sdl2.so","./lib/arcade_ndk++.so",
                                         "./lib/arcade_aalib.so", "./lib/arcade_libcaca.so", "./lib/(arcade_allegro5.so",
                                         "./lib/arcade_xlib.so", "./lib/arcade_gtk+.so", "./lib/arcade_sfml.so",
                                         "./lib/arcade_irrlicht.so", "./lib/arcade_opengl.so", "./lib/arcade_vulkan.so",
                                         "./lib/arcade_qt5.so"};
    std::list<std::string> lisIGames {"./lib/arcade_pacman.so", "./lib/arcade_nibbler.so", "./lib/arcade_qix.so",
                                      "./lib/arcade_centipede.so", "./lib/arcade_solarfox.so"};
    addIDisplaysToList(listIDisplay, prog, dl);
    addIGamesToList(lisIGames, prog, dl);
}