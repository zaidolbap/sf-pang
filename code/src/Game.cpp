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
    
    auto paddle = std::make_shared<Paddle>();
    paddle->load("graphics/paddle.png");
    paddle->setPosition(sf::Vector2f((screenWidth/2)-45,700));

    // auto paddle2 = std::make_shared<Paddle>("graphics/paddle.png", sf::Vector2f((screenWidth/2)-45, 100));

    auto ball = std::make_shared<Ball>();

    world.add("player", paddle);
    // world.add("paddle2", paddle2);
    world.add("ball", ball);

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
    auto lag = sf::Time::Zero;
    while(window.isOpen()){
        auto elapsed = clock.restart();
        // lag += elapsed;
        std::cout << "elapsedTime: " << elapsed.asSeconds() << std::endl;
        
        handleEvents();
        // either
        // handleInput(); --> put handleEvents() inside?
        // while(lag > timePerFrame){
        //     lag -= timePerFrame;
        //     update(elapsed); // or in update at the beginning?
        // }
        // render();
        // or simply
        // handleInput()
        // update(elapsed)
        // render
        // sleep remaining time todo: add FPS control, is 30 fps enough?

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
                world.updateAll(elapsed.asSeconds());
                world.drawAll(window);
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
