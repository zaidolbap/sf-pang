#pragma once

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class GameObject {
    public:
        GameObject() = default;
        virtual ~GameObject() = default;
        virtual void load(std::string filename);
        virtual void draw(sf::RenderWindow& window);
        virtual void setPosition(float const x, float const y);
        
    private:
        bool isLoaded{false};
        sf::Texture texture{};
        sf::Sprite  sprite{};
        std::string fileName{""};
};
