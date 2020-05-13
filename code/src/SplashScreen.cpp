#include "../lib/SplashScreen.hpp"

void SplashScreen::display(sf::RenderWindow& window){
    sf::Texture texture;
    if(!texture.loadFromFile("graphics/splashscreen.png")){
        // todo: throw exception?
        return;
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
                case sf::Event::EventType::MouseButtonPressed:
                case sf::Event::EventType::Closed:{
                    return;
                }
            }
        }
    }

}