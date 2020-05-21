#include "../lib/GameObjectManager.hpp"

void GameObjectManager::add(std::string const & name, std::weak_ptr<GameObject> gameObj){
    gameObjects.insert(std::make_pair(name, gameObj));
}

void GameObjectManager::remove(std::string name){
    auto searchResults = gameObjects.find(name);
    if(searchResults != gameObjects.end()){
        searchResults->second.reset();
        gameObjects.erase(searchResults);
    }
}

std::shared_ptr<GameObject> GameObjectManager::get(std::string name) const{
    auto searchResults = gameObjects.find(name);
    if(searchResults == gameObjects.end()){
        return nullptr;
    }
    return std::shared_ptr<GameObject>(searchResults->second);
}

std::size_t GameObjectManager::getObjectCount() const{
    return gameObjects.size();
}

void GameObjectManager::drallAll(sf::RenderWindow& window) {
    for(auto const & gameObject : gameObjects){
        gameObject.second->draw(window);
    }
}
