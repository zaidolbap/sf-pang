#include "SplashScreen.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

SplashScreen::Response SplashScreen::display(sf::RenderWindow& window){
    sf::Texture texture;
    if(!texture.loadFromFile("graphics/splash.png")){
        return Response::Ack;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    window.draw(sprite);
    window.display();

    sf::Event event;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::EventType::KeyPressed:
                case sf::Event::EventType::MouseButtonPressed:{
                    return Response::Ack;
                }
                case sf::Event::EventType::Closed: {
                    return Response::Exit;
                }
            }
        }
    }
}