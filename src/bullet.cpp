#include "bullet.hpp"

Bullet::Bullet(const sf::Vector2f& startPos)
{
    _bullet.setRadius(_radius);
    _bullet.setFillColor(sf::Color::Red);
    _bullet.setPosition(startPos);
    _bullet.setOrigin(_bullet.getRadius(), _bullet.getRadius());
}

void Bullet::update(const sf::Time& deltaTime)
{
    const float step = _speed * deltaTime.asSeconds(); // Adjust speed as needed
    _bullet.move(0.f, -step); // Move the bullet upwards

    // Check if the bullet is out of bounds
    if (_bullet.getPosition().y < 0.f)
    {
        _isActive = false; // Mark the bullet as not alive
    }
}

void Bullet::draw(sf::RenderWindow& window) const
{
    if (_isActive)
    {
        window.draw(_bullet); // Draw the bullet if it's alive
    }
}

bool Bullet::isActive() const
{
    return _isActive; // Return whether the bullet is alive or not
}

sf::FloatRect Bullet::collisionRect() const
{
    return _bullet.getGlobalBounds(); // Return the bounding box of the bullet
}
