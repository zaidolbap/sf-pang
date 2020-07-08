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

    if (true == intersecting){
        moveY = -moveY;
        speed += 5.0f;
        angle = ricochet;
        setPosition(collisionPos);
    } else {
        resetIntersection();
    }

    getSprite().move(moveX, moveY);    
}

void Ball::resetIntersection(){
    intersecting = false;
    ricochet     = angle;
    collisionPos = sf::Vector2f{getPosition().x, getPosition().y};
}

void Ball::calcIntersection(std::shared_ptr<Entity> paddle){
    resetIntersection();

    if(paddle->getBoundingRectangle().intersects(getBoundingRectangle())){
        intersecting = true;

        ricochet = 360.0f - (ricochet-180.0f);
        if (ricochet > 360.0f){
            ricochet -= 360.0f;
        }
        
        // ensure that the ball is not inside the paddle
        if(paddle->getBoundingRectangle().top+getBoundingRectangle().height > paddle->getBoundingRectangle().top){
            collisionPos.y = paddle->getBoundingRectangle().top-getHeight();

        } else if(getBoundingRectangle().left < paddle->getBoundingRectangle().left+paddle->getBoundingRectangle().width){
            collisionPos.x = paddle->getBoundingRectangle().left+paddle->getBoundingRectangle().width;

        } else if(getBoundingRectangle().left+getBoundingRectangle().width > paddle->getBoundingRectangle().left){
            collisionPos.x = paddle->getBoundingRectangle().left;
            
        } else if(getBoundingRectangle().top < paddle->getBoundingRectangle().top+paddle->getBoundingRectangle().height){
            collisionPos.y = paddle->getBoundingRectangle().top+paddle->getBoundingRectangle().height;
        }

        // add some randomness based on paddle's velocity
        if (paddle->getSpeed() < 0.0f){
            // moving left
            ricochet -= 20.0f;
            if (ricochet < 0.0f){
                ricochet = 360.0f - ricochet;
            }
        } else if (paddle->getSpeed() > 0.0f){
            // moving right
            ricochet += 20.0f;
            if (ricochet > 360.0f){
                ricochet = ricochet - 360;
            }
        }
    }
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