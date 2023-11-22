##
## EPITECH PROJECT, 2020
## CPE_duostumper_1_2019
## File description:
## Makefile for creating the binary
##

##### DO NOT TUTCH #######
SRC_PACMAN      =       Games/Pacman.cpp
SRC_SNAKE       =	Games/Nibbler.cpp
SRC_SFML        =	Display/SFMLlib.cpp
SRC_NCURSE	=	Display/Ncurselib.cpp
SRC_SDL		=	Display/SDLlib.cpp

OBJ_PACMAN	=	$(SRC_PACMAN:.cpp=.o)
OBJ_SNAKE	=	$(SRC_SNAKE:.cpp=.o)
##########################

########## FILES #########
SRC_CORE	=	Core.cpp                        \
                        fill_Core.cpp			\
			DlManager/DlManager.cpp
SRC_GAMES	=	Games/Nibbler.cpp		\
			Games/Pacman.cpp
SRC_LIBS	=	Display/SFMLlib.cpp		\
			Display/SDLlib.cpp		\
			Display/Ncurselib.cpp
MAIN		=	main.cpp

OBJ_CORE	=	$(SRC_CORE:.cpp=.o) $(MAIN:.cpp=.o)
OBJ_GAMES	=	$(SRC_PACMAN:.cpp=.o) $(SRC_SNAKE:.cpp=.o)
OBJ_LIBS	=	$(SRC_LIBS:.cpp=.o)
OBJ		=	$(OBJ_CORE) $(OBJ_GAMES) $(OBJ_LIBS)
##########################

########## FLAGS #########
SDL2FLAGS	=	-lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
CURSEFLAGS	=	-lcurses
SFMLFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system
UTFLAGS		=	-lcriterion --coverage
CFLAGS		=	-Wall -Wextra -g3
CPPFLAGS	=	-I include -g3
SHAREDFLAGS	=	-shared
FPIC		=	-c -fpic
##########################

########## BINARY ########
OLDCC		=	gcc
CC		=	g++
NAME		=	arcade
PACMAN_LIB	=	arcade_pacman.so
SNAKE_LIB	=	arcade_nibbler.so
SFML_LIB	=	arcade_sfml.so
NCURSE_LIB	=	arcade_ncurses.so
SDL_LIB		=	arcade_sdl2.so
TEST_NAME	=	unit_test
DEL		=	rm -rf
##########################

all:	$(NAME)

$(NAME):	$(OBJ_CORE)
	$(CC) -o $(NAME) $(OBJ_CORE) -Ilib/sfml/include $(SFMLFLAGS) $(CURSEFLAGS) $(SDL2FLAGS) -ldl -g3

core:	$(OBJ_CORE)
	$(CC) -o $(NAME) $(OBJ_CORE) -ldl

games:
	$(CC) $(FPIC) $(SRC_PACMAN)
	$(OLDCC) $(SHAREDFLAGS) -o $(PACMAN_LIB) Pacman.o
	mv $(PACMAN_LIB) lib/
	rm Pacman.o
	$(CC) $(FPIC) $(SRC_SNAKE)
	$(OLDCC) $(SHAREDFLAGS) -o $(SNAKE_LIB) Nibbler.o
	mv $(SNAKE_LIB) lib/
	rm Nibbler.o

graphicals:
	$(CC) $(FPIC) $(SRC_SFML)
	$(OLDCC) $(SHAREDFLAGS) -o $(SFML_LIB) SFMLlib.o $(SFMLFLAGS)
	mv $(SFML_LIB) lib/
	rm SFMLlib.o
	$(CC) $(FPIC) $(SRC_NCURSE)
	$(OLDCC) $(SHAREDFLAGS) -o $(NCURSE_LIB) Ncurselib.o $(CURSEFLAGS)
	mv $(NCURSE_LIB) lib/
	rm Ncurselib.o
	$(CC) $(FPIC) $(SRC_SDL)
	$(OLDCC) $(SHAREDFLAGS) -o $(SDL_LIB) SDLlib.o $(SDL2FLAGS)
	mv $(SDL_LIB) lib/
	rm SDLlib.o

tests_run:

debug: CFLAGS += -g3
debug: $(NAME)

clean:
	$(DEL) $(OBJ)

fclean: clean
	$(DEL) $(NAME)

re:	fclean all

.PHONY: re fclean clean all debug tests_run
