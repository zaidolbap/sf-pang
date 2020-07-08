#pragma once

#include "Entity.hpp"

#include <memory>

class Ball
: public Entity {
    public:
        Ball();
        Ball(std::string const & filename, sf::Vector2f const & position);
        void update(float const & elapsedTime) override;

        float getAngle() const;
        void setAngle(float const & angle);
        void calcIntersection(std::shared_ptr<Entity> paddle);

    private:
        float linearSpeedX(float const & angle);
        float linearSpeedY(float const & angle);

        float angle{0.0f};   // degrees
        float totalElapsedTime{0.0f}; // seconds

        // collision
        void resetIntersection();
        float ricochet{0.0f};
        bool intersecting{false};
        sf::Vector2f collisionPos{0.0f, 0.0f};
};