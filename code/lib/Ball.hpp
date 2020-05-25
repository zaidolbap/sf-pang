#pragma once

#include "GameObject.hpp"

class Ball
: public GameObject {
    public:
        Ball();
        Ball(std::string const & filename, sf::Vector2f const & position);
};