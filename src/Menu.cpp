#include "Menu.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window.hpp>

Menu::Response Menu::display(sf::RenderWindow& window){
    sf::Texture texture;
    if(!texture.loadFromFile("graphics/menu.png")){
        return Response::Play;
    }

    // set up clickable regions
    Item playButton{ {0, 145, 1023, 235}, Response::Play};
    Item exitButton{ {0, 383, 1023, 177}, Response::Exit};
    items.push_back(playButton);
    items.push_back(exitButton);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    window.draw(sprite);
    window.display();

    return getResponse(window);
}

Menu::Response Menu::getResponse(sf::RenderWindow& window){
    sf::Event event;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            switch (event.type){
                case sf::Event::Closed:
                    return Response::Exit;
                case sf::Event::MouseButtonPressed:
                    return handleClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }
}

Menu::Response Menu::handleClick(int const& x, int const& y){
    for(auto const & item:items) {
        if(item.rectangle.contains(sf::Vector2i(x,y))){
            return item.response;
        }
    }
    return Response::Nothing;
}
