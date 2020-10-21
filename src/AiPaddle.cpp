#include "AiPaddle.hpp"


AiPaddle::AiPaddle(std::string const & filename, sf::Vector2f const & position)
: Paddle{filename, position}
{}

void AiPaddle::update(sf::Time const & elapsed, std::shared_ptr<Entity> ball){
    // steer
    if (ball != nullptr){
        sf::Vector2f const & ballPos = ball->getPosition();
        sf::Vector2f const & pos = getPosition();
        
        if(ballPos.x < pos.x-20){
            speed -= 5.0f;
        } else if (ballPos.x > pos.x+20){
            speed += 5.0f;
        } else {
            speed = 0.0f;
        }
    } else{
        speed = 0.0f;
    }

    move(elapsed);
}