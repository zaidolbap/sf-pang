#pragma once

#include <SFML/Graphics.hpp>

enum class GameState{
    Uninitialized,
    SplashScreen,
    Paused,
    Menu,
    Playing,
    Exiting
};

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