#pragma once

#include <string>
#include <memory>
#include <map>

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.hpp"

class GameObjectManager {
    public:
        GameObjectManager()  = default;
        ~GameObjectManager() = default;

        void add (std::string const & name, std::weak_ptr<GameObject> gameObj);
        void remove(std::string name);
        std::size_t getObjectCount() const;
        std::shared_ptr<GameObject> get(std::string name) const;
        void drallAll(sf::RenderWindow& window);

    private:
        std::map<std::string, std::shared_ptr<GameObject>> gameObjects;
};
