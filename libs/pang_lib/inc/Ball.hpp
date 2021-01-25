#pragma once

#include "Entity.hpp"

#include <memory>

class Ball
: public Entity {
    public:
        Ball();
        Ball(std::string const & filename, sf::Vector2f const & position);
        void update(sf::Time const & elapsed, std::shared_ptr<Entity> paddle=nullptr) override;

        float getAngle() const;
        void setAngle(float const & angle);
        bool isMovingUp() const;

    private:
        float angle{0.0f};   // degrees
        sf::Time totalElapsed{};

        bool calcIntersection(std::shared_ptr<Entity> paddle);
};
