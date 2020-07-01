#include "../lib/Entity.hpp"

Entity::Entity(float const& speed, std::string const & filename, sf::Vector2f const & position)
: speed{speed}{
    load(filename);
    setPosition(position);
}

void Entity::load(std::string const & filename){
    if(texture.loadFromFile(filename)){
        fileName = filename;
        sprite.setTexture(texture);
        isTextureLoaded = true;
    } else {
        fileName = "";
        isTextureLoaded = false;
    }
}

void Entity::draw(sf::RenderWindow& window){
    if(isLoaded()){
        window.draw(sprite);
    }
}

void Entity::setPosition(sf::Vector2f const & position){
    if(isLoaded()){
        sprite.setPosition(position);
    }
}

sf::Vector2f Entity::getPosition() const {
    if(isLoaded()){
        return sprite.getPosition();
    }
    return sf::Vector2f{};
}

uint Entity::getWidth() const{
    return texture.getSize().x;
}

uint Entity::getHeight() const{
    return texture.getSize().y;
}

sf::Rect<float> Entity::getBoundingRectangle() const{
    auto const & size = texture.getSize();
    auto const & position = sprite.getPosition();

    return sf::Rect<float>(position.x - size.x/2, position.y - size.y/2,
                           position.x + size.x/2, position.y + size.y/2);
}

bool Entity::isLoaded() const {
    return isTextureLoaded;
}

sf::Sprite& Entity::getSprite(){
    return sprite;
}

float Entity::getSpeed() const{
    return speed;
}

void Entity::setSpeed(float const& speed){
    this->speed = speed;
}