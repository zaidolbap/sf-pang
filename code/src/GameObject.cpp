#include "../lib/GameObject.hpp"

void GameObject::load(std::string const filename){
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

void GameObject::setPosition(float const x, float const y){
    if(isLoaded){
        sprite.setPosition(x, y);
    }
}
