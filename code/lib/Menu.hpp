#pragma once

#include <SFML/Graphics.hpp>
#include<list>

class Menu {
    public:
        enum class Response {
            Nothing,
            Exit,
            Play
        };
        struct Item {
            sf::IntRect rectangle{};
            Response response{};
        };
        Response display(sf::RenderWindow& window);
    
    private:
        Response getResponse(sf::RenderWindow& window);
        Response handleClick(int const& x, int const& y);
        std::list<Item> items{};
};
