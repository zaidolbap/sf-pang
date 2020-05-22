#pragma once

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class GameObject {
    public:
        GameObject() = default;
        GameObject(std::string const & filename, sf::Vector2i const & position);
        virtual ~GameObject() = default;
        virtual void load(std::string const & filename);
        virtual void draw(sf::RenderWindow& window);
        virtual void setPosition(float const & x, float const & y);
        
    private:
        bool isLoaded{false};
        sf::Texture texture{};
        sf::Sprite  sprite{};
        std::string fileName{""};
};
