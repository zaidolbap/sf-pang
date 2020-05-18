#include "../lib/Menu.hpp"

Menu::Response Menu::display(sf::RenderWindow& window){
    sf::Texture texture;
    if(!texture.loadFromFile("graphics/mainmenu.png")){
        // todo: throw exception or return silently?
        return Response::Play;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    // set up clickable regions
    Item playButton{ {0, 145, 1023, 235}, Response::Play};
    Item exitButton{ {0, 383, 1023, 177}, Response::Exit};
    items.push_back(playButton);
    items.push_back(exitButton);

    window.draw(sprite);
    window.display();

    return getResponse(window);
}

Menu::Response Menu::getResponse(sf::RenderWindow& window){
    sf::Event event;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(sf::Event::Closed == event.type){
                return Response::Exit;
            } else if(sf::Event::MouseButtonPressed == event.type) {
                return handleClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }
}

Menu::Response Menu::handleClick(int const x, int const y){
    for(const auto& item:items) {
        if(item.rectangle.contains(sf::Vector2i(x,y))){
            return item.response;
        }
    }
    return Response::Nothing;
}
