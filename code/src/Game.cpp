#include <iostream> // todo: delete when no longer needed

#include "../lib/Game.hpp"
#include "../lib/SplashScreen.hpp"

Game::Game()
: gameState{ GameState::Uninitialized }
, window{}
{}

void Game::start(){
    std::cout << "starting" << std::endl;
    if(GameState::Uninitialized != gameState) {
        // todo: throw an exception and print an error
        std::cout << "wrong game state" << std::endl;
        return;
    }

    window.create(sf::VideoMode(1024, 768, 32), "Pang!");
    gameState = GameState::SplashScreen;

    gameLoop();
}

void Game::showSplashScreen(){
    SplashScreen splashScreen;
    splashScreen.display(window);
}

void Game::gameLoop(){
    sf::Event currentEvent;
    while(window.isOpen()){
        while(window.pollEvent(currentEvent)){
            switch(gameState){
                case GameState::SplashScreen:{
                    showSplashScreen();
                    gameState = GameState::Playing;
                }
                case GameState::Playing: {
                    window.clear(sf::Color(255, 0, 0));
                    // draw everything
                    window.display();

                    if(sf::Event::Closed ==  currentEvent.type){
                        gameState = GameState::Exiting;
                    }
                    break;
                }
                case GameState::Exiting:{
                    std::cout << "exiting" << std::endl;
                    window.close();
                    return;
                }
            }
        }
    }

}
