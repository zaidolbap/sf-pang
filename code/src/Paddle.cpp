#include "../lib/Paddle.hpp"
#include "../lib/Game.hpp"

#include <SFML/Window/Keyboard.hpp>

Paddle::Paddle()
: Entity(0.0f, "graphics/paddle.png", sf::Vector2f(0.0f, 0.0f))
, maxSpeed(600.f)
{}

Paddle::Paddle(std::string const & filename, sf::Vector2f const & position)
: Entity{0.0f, filename, position}
, maxSpeed(600.0f)
{}

void Paddle::move(float const & elapsedTime){
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

    getSprite().move(speed*elapsedTime, 0.0f);
}

void Paddle::update(float const & elapsedTime, std::shared_ptr<Entity> entity){
    // steer
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        speed -= 3.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        speed += 3.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        speed = 0.0f;
    }

    move(elapsedTime);
}
