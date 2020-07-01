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
        entity.second->update(deltaTime);
    }
}

std::tuple<bool, float, float, sf::Vector2f>
World::collide( std::shared_ptr<Ball> const & ball,
                std::shared_ptr<Entity> entity){
    
    if(ball->getBoundingRectangle().intersects(entity->getBoundingRectangle())){
        float angle = 360.0f - (ball->getAngle()-180.0f);
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        // TODO: moveY = -moveY;
        sf::Vector2f position{0.0f, 0.0f};
        if(ball->getBoundingRectangle().height > entity->getBoundingRectangle().top){
            position.x = ball->getPosition().x;
            position.y = entity->getBoundingRectangle().top - ball->getWidth()/2 -1;
        }

        if (entity->getSpeed() < 0){
            // moving left
            angle -= 20.0f;
            if (angle < 0.0f){
                angle = 360 - angle;
            }
        } else if (entity->getSpeed() > 0){
            // moving right
            angle += 20.0f;
            if (angle > 360.0f){
                angle = angle - 360;
            }
        }
        float speed = ball->getSpeed();
        speed += 5;
        return std::make_tuple(true, angle, speed, position);
    }
    return std::make_tuple(false, ball->getAngle(), ball->getSpeed(), ball->getPosition());
}