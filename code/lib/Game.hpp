#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game {
    // @todo: implement singleton pattern
    public:
        void start();

    private:
        void gameLoop();
        void showSplashScreen();
        void showMenu();
        enum class GameState{
            SplashScreen,
            Menu,
            Playing,
            Paused,
            Exiting
        };

        GameState gameState{GameState::SplashScreen};
        sf::RenderWindow window{};
        Player player{};
};
