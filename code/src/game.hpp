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
    // Game();
    Game(): gameState{ GameState::Uninitialized }
    {
        mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
    }
    // void start();
void start(){
    
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


private:
    // bool isExiting();
    bool isExiting(){
        return GameState::Exiting == gameState? true : false; 
    }
    // void gameLoop();
void gameLoop(){
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

    GameState gameState;
    sf::RenderWindow mainWindow;
};