#pragma once

#include <list>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>

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
