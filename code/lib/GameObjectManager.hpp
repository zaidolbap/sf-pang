#pragma once

#include <string>
#include <memory>
#include <map>

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.hpp"

class GameObjectManager {
    public:
        void add (std::string const & name, std::shared_ptr<GameObject> const & gameObj);
        void remove(std::string const & name);
        std::size_t getObjectCount() const;
        std::shared_ptr<GameObject> get(std::string const & name) const;
        void drawAll(sf::RenderWindow& window);
        void updateAll(float const & deltaTime);

    private:
        std::map<std::string, std::shared_ptr<GameObject>> gameObjects;
};
