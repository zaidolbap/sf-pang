#pragma once

#include <SFML/Graphics.hpp>

class Game {
    // @todo: implement singleton pattern
public:
    Game();
    void start();
    enum class GameState{
        Uninitialized,
        SplashScreen,
        Menu,
        Playing,
        Paused,
        Exiting
    };

private:
    void gameLoop();
    void showSplashScreen();
    void showMenu();

    GameState gameState;
    sf::RenderWindow window;
};
