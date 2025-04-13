#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "bullet.hpp"

class Player
{
public:
    explicit Player(const sf::RenderWindow& window);
    void handleInput(const sf::Time& deltaTime);
    void update(const sf::Time& deltaTime);
    void draw(sf::RenderWindow& window) const;

    void takeDamage(int damage);
    bool isAlive() const;
    
private:
    void initHp();
    void shoot(const sf::Time& deltaTime);

    sf::Sprite _sprite;
    sf::Texture _texture;
    const float _speed = 200.f;

    const sf::RenderWindow& _window;

    sf::RectangleShape _hpBar;
    const int _maxHp = 3;
    int _hp = 3;

    std::vector<Bullet> _bullets; // Store bullets in a vector
    sf::Clock _shootClock; // Clock to track shooting time
    const float _shootCooldown = 0.5f; // cooldown for shooting, seconds
};
