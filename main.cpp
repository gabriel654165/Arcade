//
// Created by thomas on 25/03/2021.
//

#include "prototypes.hpp"
#include "Core.hpp"
#include "DlManager/DlManager.hpp"

int main(int ac, char **av)
{
    DlManager dl;
    Core prog(&dl);

    try {
        if (ac != 2)
            throw (std::invalid_argument("No enough arguments"));
        prog.loadDisplayLib(av[1]);
        addInterfacesToLists(&prog, &dl);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    prog.gameLoop();
    return 0;
}