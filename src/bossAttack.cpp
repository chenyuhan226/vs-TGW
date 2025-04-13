#include "bossAttack.hpp"
#include <cstdlib> // For std::rand and std::srand
#include <ctime>   // For std::time

BossAttack::BossAttack(const sf::RenderWindow &window)
{
    float randomX = static_cast<float>(rand() % static_cast<int>(window.getSize().x - _attackSizeX));
    _attack.setSize(sf::Vector2f(_attackSizeX, _attackSizeY));
    _attack.setPosition(randomX, 0.f); // Start from the top of the window
    // _attack.setOrigin(_attackSizeX * 0.5f, _attackSizeY * 0.5f);
    _attack.setFillColor(sf::Color::Black);
    _windowSize = window.getSize();
}

void BossAttack::update(const sf::Time &deltaTime)
{
    if (_isActive)
    {
        float step = _speed * deltaTime.asSeconds();
        _attack.move(0.f, step); // Move downwards
        if (_attack.getPosition().y > _windowSize.y) // If it goes out of the window
        {
            _isActive = false; // Deactivate the attack
        }
    }
}

void BossAttack::draw(sf::RenderWindow &window) const
{
    if (_isActive)
    {
        window.draw(_attack);
    }
}

bool BossAttack::isActive() const
{
    return _isActive;
}

sf::FloatRect BossAttack::collisionRect() const
{
    return _attack.getGlobalBounds(); // Return the bounding box of the attack
}

void BossAttack::deactivate()
{
    _isActive = false; // Deactivate the attack
}
