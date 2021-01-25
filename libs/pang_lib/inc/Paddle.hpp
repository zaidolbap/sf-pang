#pragma once

#include "Entity.hpp"

class Paddle
: public Entity {
    public:
        Paddle();
        Paddle(std::string const & filename, sf::Vector2f const & position);
        void update(sf::Time const & elapsed, std::shared_ptr<Entity> entity=nullptr) override;

    protected:
        void move(sf::Time const & elapsed);
        float maxSpeed{600.0f};
};
