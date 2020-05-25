#include <iostream> // todo: delete when no longer needed
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>

#include "../lib/Game.hpp"
#include "../lib/SplashScreen.hpp"
#include "../lib/Menu.hpp"
#include "../lib/Ball.hpp"

void Game::start(){
    std::cout << "starting" << std::endl;
    if(GameState::SplashScreen != gameState) {
        return;
    }

    // create window and load assets
    window.create(sf::VideoMode(screenWidth, screenHeight, 32), "Pang!");
    
    auto player = std::make_shared<Player>();
    player->load("graphics/paddle.png");
    player->setPosition(sf::Vector2f((screenWidth/2)-45,700));

    // auto player2 = std::make_shared<Player>("graphics/paddle.png", sf::Vector2f((screenWidth/2)-45, 100));

    auto ball = std::make_shared<Ball>();

    gameObjectManager.add("paddle1", player);
    // gameObjectManager.add("paddle2", player2);
    gameObjectManager.add("ball", ball);

    run();
}

void Game::showSplashScreen(){
    SplashScreen splashScreen;
    SplashScreen::Response response = splashScreen.display(window);
    if(SplashScreen::Response::Ack == response){
        gameState = GameState::Menu;
    } else {
        gameState = GameState::Exiting;
    }
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
            gameState = GameState::Menu;
            break;
        default:
            gameState = GameState::Exiting;
    }
}

void Game::handleEvents(){
    sf::Event event;
    while(window.pollEvent(event)){
        if(sf::Event::Closed ==  event.type){
            gameState = GameState::Exiting;
        } 
    }
}

void Game::run(){
    // @todo: implement state pattern
    sf::Clock clock;
    while(window.isOpen()){
        auto elapsedTime = clock.restart();
        std::cout << "elapsedTime: " << elapsedTime.asSeconds() << std::endl;
        handleEvents();
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
                gameObjectManager.updateAll(elapsedTime.asSeconds());
                gameObjectManager.drawAll(window);
                window.display();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    gameState = GameState::Menu;
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
