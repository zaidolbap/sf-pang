#pragma once

#include "GameObject.hpp"

class Player
: public GameObject {
    public:
        Player();
        Player(std::string const & filename, sf::Vector2f const & position);
        
        void update(float const & elapsedTime) override;
        float getSpeed() const;

    private:
        float speed{0.0f}; // --left, ++right;
        float maxSpeed{600.0f};
};