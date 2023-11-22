/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** DlManager
*/

#include "DlManager.hpp"

DlManager::DlManager()
{
}

DlManager::~DlManager()
{
    for (auto &it: _handleListGame)
       dlclose(it);
    for (auto &it: _handleListLibs)
       dlclose(it);
}

void DlManager::removeHandlerLibs()
{
    dlclose(*_handleListLibs.begin());
    _handleListLibs.pop_front();
}

void DlManager::removeHandlerGame()
{
    dlclose(*_handleListGame.begin());
    _handleListGame.pop_front();
}

void *DlManager::openSelectedList(const char *filename, const char *entryPoint)
{
    void *handle;
    void *maker;

    handle = dlopen(filename, RTLD_LAZY);
    if (!handle) {
        throw(std::invalid_argument("Cannot open library: " + std::string(dlerror())));
    }
    if (std::string(entryPoint) == "displayEntrypoint")
        _handleListLibs.push_back(handle);
    else if (std::string(entryPoint) == "gameEntrypoint")
        _handleListGame.push_back(handle);

    maker = dlsym(handle, entryPoint);

    if (maker == NULL) {
        dlclose(handle);
        throw(std::invalid_argument("Cannot load symbol '" + std::string(entryPoint) + "': " + std::string(dlerror())) );
    }
    return maker;
}

bool DlManager::isOpenAble(const char *filename, const char *entryPoint)
{
    void *handle;
    void *maker;

    handle = dlopen(filename, RTLD_LAZY);
    if (!handle) {
        return false;
    } else
        maker = dlsym(handle, entryPoint);
    if (maker == NULL) {
        dlclose(handle);
        return false;
    }
    return true;
}