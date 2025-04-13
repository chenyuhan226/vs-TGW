#pragma once
#include <SFML/Graphics.hpp>

class BossAttack
{
public:
    BossAttack(const sf::RenderWindow &window);
    void update(const sf::Time &deltaTime);
    void draw(sf::RenderWindow &window) const;

    bool isActive() const;
    sf::FloatRect collisionRect() const; // get the bounding box of the bullet
    void deactivate(); // deactivate the attack

private:
    sf::RectangleShape _attack;
    sf::Vector2u _windowSize;
    
    float _speed = 1000.f; 
    float _attackSizeX = 60.f; // size of the attack
    float _attackSizeY = 100.f; // size of the attack
    bool _isActive = true;
};