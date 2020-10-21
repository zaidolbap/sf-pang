#pragma once

#include <string>
#include <memory>
#include <map>
#include <tuple>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity.hpp"
#include "Ball.hpp"


class World {
    public:
        void add (std::string const & name, std::shared_ptr<Entity> const & entity);
        void remove(std::string const & name);
        std::size_t getObjectCount() const;
        std::shared_ptr<Entity> get(std::string const & name) const;
        void drawAll(sf::RenderWindow& window);
        void updateAll(float const & deltaTime);

    private:
        std::map<std::string, std::shared_ptr<Entity>> entities;
};