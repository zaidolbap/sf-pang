#pragma once

#include <string>

#include "SFML/Graphics.hpp"

class GameObject {
    public:
        GameObject() = default;
        virtual ~GameObject() = default;
        virtual void load(std::string filename);
        virtual void draw(sf::RenderWindow& window);
        virtual void setPosition(float const x, float const y);
        
    private:
        bool isLoaded{false};
        sf::Sprite  sprite{};
        sf::Texture texture{};
        std::string fileName{""};
};
