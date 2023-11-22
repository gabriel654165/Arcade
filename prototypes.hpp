//
// Created by gabriel on 30/03/2021.
//

#ifndef PROTO_HPP
#define PROTO_HPP

#include "Core.hpp"
#include "DlManager/DlManager.hpp"

void addIDisplaysToList(std::list<std::string> listIDisplay, Core *prog, DlManager *dl);
void addIGamesToList(std::list<std::string> listIGames, Core *prog, DlManager *dl);
void addInterfacesToLists(Core *prog, DlManager *dl);

#endif /* !PROTO_HPP */