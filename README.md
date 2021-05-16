## Dodging Game
The user controls a spaceship (represented by *) to avoid meteors (represented by -). If the spaceship crashes into a meteor, the game would be over.
### Compilation
The game is developed with [SFML](https://www.sfml-dev.org/) on Ubuntu 20.04.

A Makefile is provided so the game can be compiled simply by running ```make```.

If the Makefile does not work, please try the following commands:
```
g++ -c meteor.cpp -I<sfml-install-path>/include
g++ -c dodgeGame.cpp -I<sfml-install-path>/include
g++ meteor.o dodgeGame.o -o dodgeGame -L<sfml-install-path>/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```
### Control
To start the game in fullscreen mode, enter ```./dodgeGame``` in the command line terminal. To start the game in a window, enter ```./dogeGame [window_width] [window_height]```.

Press _A_ to let the spaceship go left. Press _D_ to let the sapceship go right.

When the game is over, a score will be displayed. The score is calculated by _number_of_meteors_avoided / 10_. To start a new game, press _Space_.

Press _ESC_ to close the game.
### Other
Background music: _Orphans no Namida_ by Hayami Saori
