#include <iostream> // todo: delete when no longer needed

#include "../lib/game.hpp"

Game::Game()
    : gameState{ GameState::Uninitialized }
    //, mainWindow{ sf::RenderWindow{} }
{
    mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
}

void Game::start(){
    
    if(GameState::Uninitialized != gameState) {
        // todo: throw an exception and print an error
        std::cout << "wrong game state" << std::endl;
        return;
    }

    // mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
    gameState = GameState::Playing;

    while(!isExiting()){
        gameLoop();
    }
    mainWindow.close();
}

bool Game::isExiting(){
    return GameState::Exiting == gameState? true : false; 
}

void Game::gameLoop(){
    sf::Event currentEvent;

    while(mainWindow.pollEvent(currentEvent)){
        switch(gameState){
            case GameState::Playing: {
                mainWindow.clear();
                // draw everything
                mainWindow.display();

                if(sf::Event::Closed ==  currentEvent.type){
                    gameState = GameState::Exiting;
                }
                break;
            }
        }
    }
}
