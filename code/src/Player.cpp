#include "../lib/Player.hpp"
#include "../lib/Game.hpp"

#include <SFML/Window/Keyboard.hpp>

Player::Player()
: speed(0.0f)
, maxSpeed(600.f){
    load("graphics/paddle.png");
}

Player::Player(std::string const & filename, sf::Vector2f const & position)
: GameObject{filename, position}
, speed(0.0f)
, maxSpeed(600.0f)
{}

float Player::getSpeed() const{
    return speed;
}

void Player::update(float const & elapsedTime){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        speed -= 3.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        speed += 3.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        speed = 0.0f;
    }

    if(speed > maxSpeed){
        speed = maxSpeed;
    }
    if(speed < -maxSpeed){
        speed = -maxSpeed;
    }

    auto const & position_x = getPosition().x;
    auto const & textureSize_x = getSprite().getTexture()->getSize().x;
    if( position_x < 0 || position_x + textureSize_x > Game::screenWidth ){
        speed = -speed; // bounce in opposite direction with same speed
    }
    getSprite().move(speed * elapsedTime, 0.f);
}