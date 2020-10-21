// #include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>

#include "Game.hpp"
#include "SplashScreen.hpp"
#include "Menu.hpp"
#include "Ball.hpp"
#include "AiPaddle.hpp"

void Game::start(){
    if(GameState::SplashScreen != gameState) {
        return;
    }

    // create window and load assets
    window.create(sf::VideoMode(screenWidth, screenHeight, 32), "Pang!");
    
    auto paddle = std::make_shared<Paddle>();
         paddle->load("graphics/paddle.png");
         paddle->setPosition(sf::Vector2f((screenWidth/2)-45,700));
    auto aipaddle = std::make_shared<AiPaddle>("graphics/paddle.png", sf::Vector2f((screenWidth/2)-45, 40));
    auto ball = std::make_shared<Ball>();

    world.add("player", paddle);
    world.add("ball", ball);
    world.add("ai", aipaddle);

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
            break;
    }
}

void Game::handleInput(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        gameState = GameState::Menu;
        return;
    }
    sf::Event event;
    while(window.pollEvent(event)){
        if(sf::Event::Closed ==  event.type){
            gameState = GameState::Exiting;
            return;
        } 
    }
}

void Game::run(){
    // @todo: implement state pattern
    sf::Clock clock;
    while(window.isOpen()){
        auto elapsed = clock.restart();
        // std::cout << "elapsedTime: " << elapsed.asSeconds() << std::endl;
        
        handleInput();

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
                world.updateAll(elapsed);
                world.drawAll(window);
                window.display();

                if (timePerFrame - elapsed > sf::Time{}){
                    // sleep only if the elapsed time is smaller than time per frame
                    std::this_thread::sleep_for(std::chrono::milliseconds( (timePerFrame - elapsed).asMilliseconds() ));
                }
                break;
            }
            case GameState::Exiting:{
                window.close();
                return;
            }
        }
    }
}
