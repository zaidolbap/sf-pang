#include "../lib/Ball.hpp"
#include "../lib/Game.hpp"

#include <cmath>

// to be replaced by std::numbers::pi defined in #include <numbers> in c++20 when it's supported
constexpr float pi(){
    return std::atan(1.0f)*4.0f;
}

constexpr float deg2rad(float const & angle){
    return angle * (pi()/180.f);
}

constexpr float reorient(float angle){
    // ensure that 0 is up instead of to the right in our coordinate system
    angle -= 90; 
    if(angle < 0){
        angle = 360.0f + angle;
    }
    return angle;
}

constexpr float linearSpeedX(float const & angle){
    return std::cos(deg2rad(reorient(angle)));
}

constexpr float linearSpeedY(float const & angle){
    return std::sin(deg2rad(reorient(angle)));
}

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

void Ball::update(float const & elapsedTime, std::shared_ptr<Entity> paddle){
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
    // collision with top/bottom screen boundary
    if( getPosition().y <= 0 ||
        getPosition().y + getHeight() + moveY >= Game::screenHeight){
        // reset with randomized angle
        getSprite().setPosition(Game::screenWidth/2, Game::screenHeight/2);
        angle = static_cast<float>(std::rand()%360);
        speed = 220.0f;
        totalElapsedTime = 0.0f;
    }

    if (true == calcIntersection(paddle)){
        moveY = -moveY;
        speed += 5.0f;
    }

    getSprite().move(moveX, moveY);    
}

bool Ball::calcIntersection(std::shared_ptr<Entity> paddle){
    if (nullptr == paddle){
        return false;
    }

    if(paddle->getBoundingRectangle().intersects(getBoundingRectangle())){
        // ensure that the ball is not inside the paddle
        sf::Vector2f position{getPosition()};
        if(isMovingUp()){
            if(getBoundingRectangle().top < paddle->getBoundingRectangle().top+paddle->getBoundingRectangle().height){
                position.y = paddle->getBoundingRectangle().top+paddle->getBoundingRectangle().height;

            } else if(getBoundingRectangle().left+getBoundingRectangle().width > paddle->getBoundingRectangle().left){
                position.x = paddle->getBoundingRectangle().left;

            } else if(getBoundingRectangle().left < paddle->getBoundingRectangle().left+paddle->getBoundingRectangle().width){
                position.x = paddle->getBoundingRectangle().left+paddle->getBoundingRectangle().width;

            }         
        } else{
            if(getBoundingRectangle().top+getBoundingRectangle().height > paddle->getBoundingRectangle().top){
                position.y = paddle->getBoundingRectangle().top-getHeight();

            } else if(getBoundingRectangle().left < paddle->getBoundingRectangle().left+paddle->getBoundingRectangle().width){
                position.x = paddle->getBoundingRectangle().left+paddle->getBoundingRectangle().width;

            } else if(getBoundingRectangle().left+getBoundingRectangle().width > paddle->getBoundingRectangle().left){
                position.x = paddle->getBoundingRectangle().left;
            }
        }
        setPosition(position);

        // calculate ricochet angle
        angle = 360.0f - (angle-180.0f);
        if (angle > 360.0f){
            angle -= 360.0f;
        }
        // add some randomness based on paddle's velocity
        if (paddle->getSpeed() < 0.0f){
            // moving left
            angle -= 20.0f;
            if (angle < 0.0f){
                angle = 360.0f - angle;
            }
        } else if (paddle->getSpeed() > 0.0f){
            // moving right
            angle += 20.0f;
            if (angle > 360.0f){
                angle = angle - 360;
            }
        }

        return true;

    } else {
        return false;
    }
}

void Ball::setAngle(float const& angle){
    this->angle = angle;
}

float Ball::getAngle() const{
    return angle;
}

bool Ball::isMovingUp() const{
    if(linearSpeedY(angle) < 0.0f){
        return true;
    } else {
        return false;
    }
}

