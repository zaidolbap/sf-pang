#include "../lib/Ball.hpp"
#include "../lib/Game.hpp"

#include <cmath>

// to be replaced by std::numbers::pi defined in #include <numbers> in c++20 when it's supported
constexpr float pi() { return std::atan(1.0f)*4.0f; }

Ball::Ball()
: Entity{230, "graphics/ball.png", sf::Vector2f(Game::screenWidth/2, Game::screenHeight/2)}
, angle{0}
, totalElapsedTime{0}
{}

Ball::Ball(std::string const & filename, sf::Vector2f const & position)
: Entity{230, filename, position}
, angle{0}
, totalElapsedTime{0}
{}

void Ball::update(float const & elapsedTime){
    totalElapsedTime += elapsedTime;

    if(totalElapsedTime < 1.0f){
        // delay game until 1 seconds have passed
        return;
    }

    auto const moveAmount = speed * elapsedTime;
    auto moveX = linearSpeedX(angle) * moveAmount;
    auto moveY = linearSpeedY(angle) * moveAmount;

    // collision with side screen boundaries
    if(   getPosition().x + moveX <= 0
       || getPosition().x + getWidth() + moveX >= Game::screenWidth){
        // ricochet: add a small variation to the angle of 20 degs 
        // if ball hits to +-10deg to make it more interesting
        angle = 360.0f - angle;
        if(angle > 260.0f && angle < 280.0f){
            angle += 20.0f;
        }
        if(angle > 80.0f && angle < 100.0f){
            angle += 20.0f;
        }
        moveX = -moveX;
    }

    // collision with top screen boundary
    if( getPosition().y <= 0){
        angle = 180 - angle;
        moveY = -moveY;
    }
    // collision with bottom screen boundary
    if( getPosition().y + getHeight() + moveY >= Game::screenHeight){
        // reset with randomized angle
        getSprite().setPosition(Game::screenWidth/2, Game::screenHeight/2);
        angle = static_cast<float>(std::rand()%360);
        speed = 220.0f;
        totalElapsedTime = 0.0f;
    }

    // calculate collision with paddle
    getSprite().move(moveX, moveY);    
}

constexpr float reorient(float angle){
    // ensure that 0 is up instead of to the right in our coordinate system
    angle -= 90; 
    if(angle < 0){
        angle = 360.0f + angle;
    }
    return angle;
}

constexpr float deg2rad(float const & angle){
    return angle * (pi()/180.f);
}

float Ball::linearSpeedX(float const & angle){
    return std::cos(deg2rad(reorient(angle)));
}

float Ball::linearSpeedY(float const & angle){
    return std::sin(deg2rad(reorient(angle)));
}

void Ball::setAngle(float const& angle){
    this->angle = angle;
}

float Ball::getAngle() const{
    return angle;
}