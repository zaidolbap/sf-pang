#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class SplashScreen {
    public:
        enum class Response {
            Exit,
            Ack
        };
        Response display(sf::RenderWindow& window);
};
