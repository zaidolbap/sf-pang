#pragma once

#include <string>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>


class Entity {
    public:
        Entity() = default;
        Entity(float const& speed, std::string const & filename, sf::Vector2f const & position);
        virtual ~Entity() = default;

        virtual void load(std::string const & filename);
        virtual void draw(sf::RenderWindow& window);
        virtual void update(sf::Time const & elapsedTime, std::shared_ptr<Entity> entity=nullptr){};

        virtual void setPosition(sf::Vector2f const & position);
        virtual sf::Vector2f getPosition() const;
        virtual uint getWidth()  const;
        virtual uint getHeight() const;
        virtual sf::FloatRect getBoundingRectangle() const;
        virtual float getSpeed() const;
        virtual void setSpeed(float const & speed);

        virtual bool isLoaded() const;

    protected:
        sf::Sprite& getSprite();
        float speed{0.0f}; // pixels/second: --left, ++right

    private:
        bool isTextureLoaded{false};
        sf::Texture texture{};
        sf::Sprite  sprite{};
        std::string fileName{""};
};
