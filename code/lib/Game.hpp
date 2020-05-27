#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

#include "Player.hpp"
#include "GameObjectManager.hpp"

class Game {
    public:
        static Game& instance() {
            static Game game;
            return game;    
        }
        Game(Game const &) = delete;
        void operator=(Game const &) = delete;

        void start();
        static uint const screenWidth{1024};
        static uint const screenHeight{768};

        

    private:
        Game() = default;
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
