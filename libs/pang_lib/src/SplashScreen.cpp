#include "SplashScreen.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

        #include <unistd.h>
        #include <stdio.h>

SplashScreen::Response SplashScreen::display(sf::RenderWindow& window){
        // YOU ARE HERE:
        // WHEN DEBUG -> /home/zaidolbap/repos/pang/build/apps
        // WHEN cmake   -> /home/zaidolbap/repos/pang v
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("Current working dir: %s\n", cwd);
        //
    
    sf::Texture texture;
    if(!texture.loadFromFile("img/splash.png")){
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