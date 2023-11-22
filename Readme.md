# **MyArcade**

Launch the Arcade program:
Run the compilation rules for games, graphics, and all from the Makefile.
Once this is done, our encapsulated libraries will be located in the **lib/** folder.

bash
`./arcade ./[path to one of our graphic libraries].so`

---

## **User Documentation**

### **Getting Started with the Arcade Program:**
The menu allows the player to enter their name, **select** the game and graphic library, and view the best scores as in an arcade machine.

**Menu Commands:**
- Change game/lib: Right and Left arrows
- Select game or lib: Up and Down arrows
- Launch the game: Enter key

**Options:**
- Change game: F3 and F4
- Change graphic library: F1 and F2

**In-Game Options:**
- P key: pause/resume the game
- R key: Reset the game
- E key: return to the menu
- Escape key: exit the arcade machine

### **Pacman: Commands**
**Directions:**
- Right arrow: turn right
- Left arrow: turn left

**Pacman: Game Rules**
In this game, you will **control** the iconic Pac-Man. The goal is to collect as many pac-dots while avoiding being touched by ghosts. Your score increases proportionally to the number of pac-dots collected. Four bonuses are present at each corner of the field. Collecting these bonuses allows you to eliminate the ghosts, which will reappear in their base before resuming their course after a short delay.

### **Nibbler: Commands**
**Directions:**
- Right arrow: turn right
- Left arrow: turn left

**Special Keys:**
- Up arrow: increase speed
- Down arrow: decrease speed

**Nibbler: Game Rules**
You **embody** a snake, and you must eat as many items as possible on the map. There are two types of items: points and drinks (x2). When you eat an item:
- The snake's size increases.
- The score increase 
- The game's speed increase
The higher the speed, the greater the gain from collecting items.
Be careful, if the game speed is too low, the player won't be able to earn any points.
The game is over when the snake runs into a wall or eats its own tail.

---

# **Technical Documentation**

Our project is divided into 2 interfaces. One for game creation "Games/IGames.hpp," another for encapsulating graphic libraries "Display/IDisplay.hpp." The games Pacman.cpp and Nibbler.cpp have already been created using the IGames model. To create your own, you only need to create a class inheriting from IGames and fill in the following methods:

- `void update()`: Based on the "Events" enumerator, move the different elements of your game, which is in the form of `std::list<std::list<Map_Element>> _map`. This function drives the game forward.
- `void reset()`: This function resets all elements of the game to their initial values and is called when restarting a game.
- `int getScore()`: This function returns the score that can be updated in the `update` function according to your rules.
- `std::list<std::list<Map_Element>> getMap()`: This function returns the map of your game, which is your list of elements that you update in `update`.
- `void makeAction(Events event)`: This function is only called in your program to move your main character based on the Events enum (can be called in update).
- `std::map<Map_Element, std::string> getAssets()`: This function returns a list of enumerators, accompanied by their assets, their texture, or rather the path to each of them, which can be filled in from the constructor and modified.
- `bool isEnd()`: This function returns the boolean that is true when the game is over, otherwise it remains false.

Don't forget to add the .cpp of your classes in SRC_GAMES in our Makefile as well as the creation of the shared library for it. So compile with the "make games" rule, then run the program, then select your game.

As for the graphical interfaces, 3 have been created. One encapsulating SDL2, one Ncurses, and one SFML. To create your own, you only need to create a class inheriting from IDisplay and fill in the following methods:

- `~IDisplay()`: In your destructor, you must destroy all the resources created and necessary for the display of your library.
- `void displayMenu(std::list<std::pair<std::string, bool>>std::list<std::pair<std::string, bool>>, Selected_Field)`: This function takes as an argument the lists of .so games and graphic library available as well as the selected chap based on the pressed keys.
- `void displayMap(std::list<std::list<Map_Element>>)`: This function is only used to display the map on your screen with the argument you have.
- `void displayScore(int)`: This function displays the game score on your screen given as a parameter of the function.
- `void displayBestScores(std::list<std::string>)`: This function displays the list of the best scores of the game on your screen, always given as a parameter of the function.
- `void displayUserName(std::string)`: This function displays on your screen the name given as a parameter.
- `void displayEnd()`: This function is called at the end of the game and is used to display the game over menu, for example.
- `void userNameSelection()`: This function is called at the very beginning of the program and displays the selection of the name that the player will choose for his game.
- `Events getLastInput()`: This function uses the detection of keys from your graphic library and returns an Events enumerator based on the desired action.
- `void setAssets(std::map<Map_Element, std::string>)`: This function allows you to assign textures in advance with the list of assets and their paths from the game. So as not to have to create a texture for each display.
- `std::string getUsername()`: This function only returns the username that the player will have chosen after going through the "userNameSelection()" method.

Don't forget to add the .cpp of your classes in SRC_LIBS in our Makefile as well as the creation of the shared library for it. So compile with the "make graphical" rule, then run the program.
