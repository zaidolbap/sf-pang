#pragma once

#include "Paddle.hpp"

class AiPaddle
: public Paddle {
    public:
        AiPaddle() = default;
        AiPaddle(std::string const & filename, sf::Vector2f const & position);
        void update(float const & elapsedTime, std::shared_ptr<Entity> ball=nullptr) override;
};