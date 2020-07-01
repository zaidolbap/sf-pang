#pragma once

#include "Entity.hpp"

class Ball
: public Entity {
    public:
        Ball();
        Ball(std::string const & filename, sf::Vector2f const & position);
        void update(float const & elapsedTime) override;

        float getAngle() const;
        void setAngle(float const & angle);

    private:
        float linearSpeedX(float const & angle);
        float linearSpeedY(float const & angle);

        float angle{0.f};   // degrees
        float totalElapsedTime{0.f}; // seconds
};