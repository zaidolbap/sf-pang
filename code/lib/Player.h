#pragma once

#include "GameObject.hpp"

class Player
: public GameObject {
    public:
        Player() = default;
        Player(std::string const & filename, sf::Vector2i const & position)
        : GameObject{filename, position}
        {}
};