#include "Game.hpp" 
#include <cstdlib> // for rand() and srand()
#include <iostream> // for std::cerr


int main() {
    srand(time(NULL));
    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}