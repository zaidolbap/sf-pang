#include "../lib/GameObject.hpp"

GameObject::GameObject(std::string const & filename, sf::Vector2i const & position){
    load(filename);
    setPosition(position.x, position.y);
}

void GameObject::load(std::string const & filename){
    if(texture.loadFromFile(filename)){
        fileName = filename;
        sprite.setTexture(texture);
        isLoaded = true;
    } else {
        fileName = "";
        isLoaded = false;
    }
}

void GameObject::draw(sf::RenderWindow& window){
    if(isLoaded){
        window.draw(sprite);
    }
}

void GameObject::setPosition(float const & x, float const & y){
    if(isLoaded){
        sprite.setPosition(x, y);
    }
}
