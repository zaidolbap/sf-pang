#include <iostream> // todo: delete when no longer needed

 #include "../lib/Game.hpp"

int main() {
    std::cout << "pang!" << std::endl;

    Game::instance().start();
    
    return 0;
}