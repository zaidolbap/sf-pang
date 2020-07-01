#pragma once

#include "Entity.hpp"

class Paddle
: public Entity {
    public:
        Paddle();
        Paddle(std::string const & filename, sf::Vector2f const & position);
        void update(float const & elapsedTime) override;

    private:
        float maxSpeed{600.0f};
};