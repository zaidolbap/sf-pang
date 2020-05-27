#include "../lib/GameObject.hpp"

GameObject::GameObject(std::string const & filename, sf::Vector2f const & position){
    load(filename);
    setPosition(position);
}

void GameObject::load(std::string const & filename){
    if(texture.loadFromFile(filename)){
        fileName = filename;
        sprite.setTexture(texture);
        isTextureLoaded = true;
    } else {
        fileName = "";
        isTextureLoaded = false;
    }
}

void GameObject::draw(sf::RenderWindow& window){
    if(isLoaded()){
        window.draw(sprite);
    }
}

void GameObject::setPosition(sf::Vector2f const & position){
    if(isLoaded()){
        sprite.setPosition(position);
    }
}

sf::Vector2f GameObject::getPosition() const {
    if(isLoaded()){
        return sprite.getPosition();
    }
    return sf::Vector2f{};
}

uint GameObject::getWidth() const{
    texture.getSize().x;
}

uint GameObject::getHeight() const{
    texture.getSize().y;
}

sf::Rect<float> GameObject::getBoundingRectangle() const{
    auto const & size = texture.getSize();
    auto const & position = sprite.getPosition();

    return sf::Rect<float>( position.x - size.x/2, position.y - size.y/2,
                            position.x + size.x/2, position.y + size.y/2);
}

bool GameObject::isLoaded() const {
    return isTextureLoaded;
}

sf::Sprite& GameObject::getSprite(){
    return sprite;
}