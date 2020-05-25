#include "../lib/Ball.hpp"
#include "../lib/Game.hpp"

Ball::Ball(){
    load("graphics/ball.png");
    setPosition(sf::Vector2f(Game::screenWidth/2, Game::screenHeight/2));
}

Ball::Ball(std::string const & filename, sf::Vector2f const & position){
    load(filename);
    setPosition(position);
}