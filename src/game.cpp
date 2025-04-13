#include "game.hpp"

Game::Game()
    : _window(sf::VideoMode(2300, 1300), "Shoot game"), _player(_window), boss(_window) 
{
    _window.setFramerateLimit(60);
    _window.setPosition(sf::Vector2i(50, 50));
}

void Game::run()
{
    sf::Clock clock;
    while (_window.isOpen())
    {
        sf::Time dt = clock.restart();
        processEvents();
        update(dt);
        draw();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            _window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            _window.close();
    }
}
void Game::update(sf::Time dt)
{
    _player.handleInput(dt);
    _player.update(dt);
    boss.update(dt); // Update boss if needed
    // Update other game elements
}
void Game::draw()
{
    _window.clear(sf::Color::White);
    _player.draw(_window);
    boss.draw(_window); 
    // Draw other game elements
    _window.display();
}