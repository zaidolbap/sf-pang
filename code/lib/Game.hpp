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
        Paused,
        Menu,
        Playing,
        Exiting
    };

private:
    void gameLoop();
    void showSplashScreen();
    void showMenu();

    GameState gameState;
    sf::RenderWindow window;
};
