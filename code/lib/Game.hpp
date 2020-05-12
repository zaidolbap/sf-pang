#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.hpp"

class Game {
    // @todo: implement singleton pattern
public:
    Game();
    void start();

private:
    bool isExiting();
    void gameLoop();

    GameState gameState;
    sf::RenderWindow mainWindow;
};
