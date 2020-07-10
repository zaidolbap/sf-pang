#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

#include "Paddle.hpp"
#include "World.hpp"

class Game {
    public:
        Game(Game const &) = delete;
        void operator=(Game const &) = delete;
        Game(Game&&) = delete;

        /// \brief return game instance
        static Game& instance() {
            static Game game;
            return game;
        }
        static uint const screenWidth{1024};
        static uint const screenHeight{768};

        void start();

    private:
        Game() = default;

        void run();
        void showSplashScreen();
        void showMenu();
        void handleInput();

        enum class GameState{
            SplashScreen,
            Menu,
            Playing,
            Paused,
            Exiting
        };

        GameState gameState{GameState::SplashScreen};
        sf::RenderWindow window{};
        World world{};

        constexpr static float FPS{30.f};
        sf::Time const timePerFrame = sf::seconds(1.0f/FPS);
};
