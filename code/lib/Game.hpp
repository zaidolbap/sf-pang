#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.hpp"

class Game {
    // @todo: implement singleton pattern
public:
    Game();
    void start();

private:
    void gameLoop();
    void showSplashScreen();

    GameState gameState;
    sf::RenderWindow window;
};
