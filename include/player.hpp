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
    sf::FloatRect collisionRect() const;
    std::vector<Bullet>& getBullets();
    void cleanupBullets();
    
private:
    void initHp();
    void shoot(const sf::Time& deltaTime);

    sf::Sprite _sprite;
    sf::Texture _texture;
    const float _speed = 300.f;

    const sf::RenderWindow& _window;

    sf::RectangleShape _hpBar;
    float _hp = 3.f; // Current HP
    const float _maxHp = 3.f; // Maximum HP
    const float _initialHpBarWidth = 300.f; // Initial width of the HP bar

    std::vector<Bullet> _bullets; // Store bullets in a vector
    sf::Clock _shootClock; // Clock to track shooting time
    const float _shootCooldown = 1.0f; // cooldown for shooting, seconds
};
