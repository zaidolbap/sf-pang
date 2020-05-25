#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

#include "Player.hpp"
#include "GameObjectManager.hpp"

class Game {
    // @todo: implement singleton pattern
    public:
        void start();
        static uint const screenWidth{1024};
        static uint const screenHeight{768};

    private:
        void run();
        void showSplashScreen();
        void showMenu();
        void handleEvents();
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
