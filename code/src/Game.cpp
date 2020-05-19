#include <iostream> // todo: delete when no longer needed

#include "../lib/Game.hpp"
#include "../lib/SplashScreen.hpp"
#include "../lib/Menu.hpp"

Game::Game()
: gameState{GameState::Uninitialized}
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
    gameState = GameState::Menu;
}

void Game::showMenu(){
    Menu menu;
    Menu::Response response = menu.display(window);
    switch(response){
        case Menu::Response::Play:
            gameState = GameState::Playing;
            break;
        case Menu::Response::Exit:
            gameState = GameState::Exiting;
            break;
        case Menu::Response::Nothing:
            //gameState = GameState::Menu;
            break;
        default:
            std::cout << "wrong menu response" << std::endl;
            //throw exception?
    }
}

void Game::gameLoop(){
    // @todo: implement state pattern
    sf::Event event;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            switch(gameState){
                case GameState::SplashScreen:{
                    showSplashScreen();
                    break;
                }
                case GameState::Menu:{
                    showMenu();
                    break;
                }
                case GameState::Playing: {
                    window.clear(sf::Color(255, 0, 0));
                    // draw everything
                    window.display();

                    if(sf::Event::Closed ==  event.type){
                        gameState = GameState::Exiting;
                    } else {
                        break;
                    }
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
