#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Player.hpp"
#include "GameObjectManager.hpp"

class Game {
    // @todo: implement singleton pattern
    public:
        void start();
        static uint const screenWidth{1024};
        static uint const screenHeight{768};

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
        GameObjectManager gameObjectManager{};
};
