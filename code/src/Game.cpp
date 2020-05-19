#include <iostream> // todo: delete when no longer needed

#include "../lib/Game.hpp"
#include "../lib/SplashScreen.hpp"
#include "../lib/Menu.hpp"

void Game::start(){
    std::cout << "starting" << std::endl;
    if(GameState::SplashScreen != gameState) {
        // todo: throw an exception?
        std::cout << "wrong game state" << std::endl;
        return;
    }

    // create window and load assets
    window.create(sf::VideoMode(1024, 768, 32), "Pang!");
    player.load("graphics/paddle.png");
    player.setPosition(((1024/2)-45),700);

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
                    window.clear(sf::Color(0, 0, 0));
                    // draw everything
                    player.draw(window);
                    window.display();

                    if(sf::Event::KeyPressed == event.type){
                        if(sf::Keyboard::Escape == event.key.code){
                            gameState = GameState::Menu;
                            break;
                        }
                    } else if(sf::Event::Closed ==  event.type){
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
