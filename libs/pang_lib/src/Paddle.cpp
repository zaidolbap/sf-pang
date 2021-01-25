#include "Paddle.hpp"
#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>

Paddle::Paddle()
: Entity(0.0f, "img/paddle.png", sf::Vector2f(0.0f, 0.0f))
, maxSpeed(600.f)
{}

Paddle::Paddle(std::string const & filename, sf::Vector2f const & position)
: Entity{0.0f, filename, position}
, maxSpeed(600.0f)
{}

void Paddle::move(sf::Time const & elapsed){
    if(speed > maxSpeed){
        speed = maxSpeed;
    }
    if(speed < -maxSpeed){
        speed = -maxSpeed;
    }

    // bounce in opposite direction with same speed
    auto pos = getPosition();
    if(pos.x < 0) {
        pos.x = 0;
        setPosition(pos);
        speed = -speed;
    }
    if(pos.x + getWidth() > Game::screenWidth){
        pos.x = Game::screenWidth - getWidth();
        setPosition(pos);
        speed = -speed;
    } 

    getSprite().move(speed*elapsed.asSeconds(), 0.0f);
}

bool isNoKeyPressed()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        return false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        return false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        return false;
    }
    return true;
}

void Paddle::update(sf::Time const & elapsed, std::shared_ptr<Entity> entity){
    // steer
    if( isNoKeyPressed()){
        
        if (speed < 0.0f) {
            speed += 3.0f;
            speed =  std::min(speed, 0.0f);
        } else {
            speed -= 3.0f;
            speed =  std::max(speed, 0.0f);
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        speed -= 5.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        speed += 5.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        speed = 0.0f;
    }

    move(elapsed);
}
