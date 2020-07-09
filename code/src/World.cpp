#include "../lib/World.hpp"

void World::add(std::string const & name, std::shared_ptr<Entity> const & entity){
    entities.insert(std::make_pair(name, entity));
}

void World::remove(std::string const & name){
    auto searchResults = entities.find(name);
    if(searchResults != entities.end()){
        searchResults->second.reset();
        entities.erase(searchResults);
    }
}

std::shared_ptr<Entity> World::get(std::string const & name) const{
    auto searchResults = entities.find(name);
    if(searchResults == entities.end()){
        return nullptr;
    }
    return std::shared_ptr<Entity>(searchResults->second);
}

std::size_t World::getObjectCount() const{
    return entities.size();
}

void World::drawAll(sf::RenderWindow& window) {
    for(auto const & entity : entities){
        entity.second->draw(window);
    }
}

void World::updateAll(float const & deltaTime){
    for(auto const & entity: entities){
        if(entity.first == "ball"){
            if(std::static_pointer_cast<Ball>(entity.second)->isMovingUp()){
                entity.second->update(deltaTime, get("ai"));
            } else {
                entity.second->update(deltaTime, get("player"));
            }
        } else if(entity.first == "ai"){
            entity.second->update(deltaTime, get("ball"));
        } else {
            entity.second->update(deltaTime);
        }
    }
}
