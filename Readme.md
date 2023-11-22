# MyArcade

Lancer le programme Arcade :
Lancez les règles de compilation games, graphicals & all du Makefile.
Une fois cela fais nos librairies encapsulés se trouverons dans le dosser lib/
./arcade ./[chemin vers une de nos librairie graphique].so
_________________________________________________________________________________________________________________________________________________________________________

Documentation utilisateur :
Prise en main du programme Arcade :
Le menu permet au joueur de rentrer son nom, de selectionner le jeux et la lib graphique, de voir les meilleurs scores comme dans une borne d'arcade.
Commandes dans le menu :
     Changer de jeux/ lib : flèches Droite et Gauche
     Selectionner Jeux ou lib : flèches Haut et Bas
     Lancer le jeu : Touche Entrée
Options :
	Changer de jeux : F3 et F4
    Changer de librairie graphique : F1 et F2
Options en jeu :
	touche P : mettre en pause/reprendre le jeu
	touche R : Reset le jeu
	touche E : retour au menu
	touche Echap : quitte la borne d'arcade

Pacman : Commandes
Directions :
	flèche droite : tourner à droite
	flèche gauche : tourner à gauche
Pacman : Règles du jeu
Dans ce jeu, vous controllerez l'emblématique Pac-Man. Le but du jeu est de récolter
le plus de pac-gomme tout en évitant de se faire toucher par les fantômes. Votre score
augmente proportionnellement au nombre de pac-gomme récolté.
Quatres bonus sont présents à chaques coints du terrain.
Récolter ces bonus vous permettra d'éliminer les fantômes qui réapparaitront dans leur
base, avant de reprendre leur course après un court délais.

Nibbler : Commandes
Directions :
	flèche droite : tourner à droite
	flèche gauche : tourner à gauche
Touches Spéciales :
	flèche haut : augmente la vitesse
	flèche bas : diminue la vitesse
Nibbler : Règles du jeu
Vous incarner un serpent et vous devez manger le plus d'item présent sur la map.
il existe deux types d'item : les points et les boissons (x2)
L'orsque vous mangerez un item :
	 -la taille du serpent augmente.
	 -le score augmente.
	 -la vitesse de jeu augmente.
Plus la vitesse augmente, plus le gain en rammassant les items est grand.
Attention, si la vitesse de jeu est trop faible, le joeur ne pourras pas gagner de points.
La partie est finie l'orsque le serpent rentre dans un mur ou l'orsque qu'il se mange la queue.

_________________________________________________________________________________________________________________________________________________________________________

Documentation technique :
Notre projet est divisé en 2 interfaces. Une pour la création de jeux "Games/IGames.hpp", une autre pour l'encapsulation de librairies graphiques "Display/IDisplay.hpp".
Les Jeux Pacman.cpp et Nibbler.cpp on déjà été créer avec le model de IGames.
Pour en créer un a votre tours vous aurez seulement a créer une classe héritant de IGames et de remplir les methodes suivantes :
    - void update() : En fonction des Enumérateurs de type "Events" vous ferez bougez les différents éléments de votre jeu qui est sous la forme std::list<std::list<Map_Element>> _map. C'est cette fonction qui fera avancer le jeu.
    - void reset() : cette fonction remettra a ses valeures de départ tout les eléments du jeu. Elle sera appelé lors d'un recommencement de partie.
    - int getScore() :  cete fonction retournera le score qui peu être mis a jour dans la fonction update seln vos règles.
    - std::list<std::list<Map_Element>> getMap() : cette fonction retourne la map de votre jeu soit votre liste d'éléments que vous mettez a jour dans update.
    - void makeAction(Events event) : Cette fonction est uniquement appelé dans votre programme pour faire bouger votre personneage principal en fonction des énum Events (peux être appelé dans update).
    - std::map<Map_Element, std::string> getAssets() : cette fonction retournera une list d'enumérateurs, accompagnés de leurs assets, leur texture, ou plutot le chemin vers chacun d'eux qui peeux être remplit dès le constructeur et modifié.
    - bool isEnd() :  cette fonction retourne le booléan qui lorsque la partie est fine est a true, sinon il reste a false.
N'oubliez pas de rajouter les .cpp de vos classes dans SRC_GAMES dans notre Makefile ainsi que la création de la lirairie partagée pour celle ci.
Ainsi compilez avec la règle "make games" puis lancer le programme, puis selectionnez votre jeu.

Quand aux interfaces graphiques 3 on était créeés. L'un qui encapsule la SDL2, une la Ncurse, et une la Sfml. Pour en créer un a votre tours vous aurez seulement a créer une classe héritant de IDisplay et de remplir les methodes suivantes :
    - ~IDisplay() : dans votre destructeur vous devrez detruire toute les rescources créeés et nécessaires a l'affichage de votre librairie.
    - void displayMenu(std::list<std::pair<std::string, bool>>std::list<std::pair<std::string, bool>>, Selected_Field) : cette fonction prends en argumment les listes de jeux .so et de librairie graphique .so disponibles ainsi que le chap selectionné en fonction des touches pressées.
    - void displayMap(std::list<std::list<Map_Element>>) : Cette fonction sert uniquement a display la map sur votre ecran avec l'agrument que vous avez.
    - void displayScore(int) : cette fonction affiche le score du jeu sur votre ecran donné en paramètre de la fonction
    - void displayBestScores(std::list<std::string>) : cette fonction affiche la liste des meuilleurs scores du jeu sur votre ecran, toujours donné en paramètre de la fonction.
    - void displayUserName(std::string) :  cette fonction affichae sur votre ecran le nom donné en paramètre.
    - void displayEnd() : cette fonction estv appelé a la,fin du jeu et est utilisé pour afficher le menu game over par exmeple.
    - void userNameSelection() : Cette fonction est appéelée au tout début du programme et affiche la selection du nom que va prendre le joeur pour sa partie.
    - Events getLastInput() : cette fontion utilise la detection des touches de votre librairie graphique et retourne un énumérateur Events en fonction de l'actioin voulue. 
    - void setAssets(std::map<Map_Element, std::string>) : cette fonction permet d'assigner des textures a l'avance avec la liste d'asset et de ses chemins du jeu. Pour ne pas avoir a créer une texture pour chaques affichages.
    - std::string getUsername() : Cette fonction renvoie seulement le nom d'utilisateur qu'aura choisis le joeur apres être passé dans la methode "userNameSelection()".
N'oubliez pas de rajouter les .cpp de vos classes dans SRC_LIBS dans notre Makefile ainsi que la création de la lirairie partagée pour celle ci.
Ainsi compilez avec la règle "make graphical" puis lancer le programme.