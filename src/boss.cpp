#include "boss.hpp"
#include <cstdlib> // For std::rand and std::srand

Boss::Boss(const sf::RenderWindow &window) : _window(window), _windowX(window.getSize().x), _windowY(window.getSize().y)
{
    if (!_texture.loadFromFile("data/boss.png"))
        throw std::runtime_error("Failed to load boss image!");
    _sprite.setTexture(_texture);
    _texture.setSmooth(true);
    _sprite.setScale(0.5f, 0.5f); // Scale down the sprite to make it smaller
    _sprite.setOrigin(_texture.getSize().x * 0.5f, _texture.getSize().y * 0.5f);
    _sprite.setPosition(_window.getSize().x * 0.5f, _sprite.getGlobalBounds().height * 0.5f + 60.f);
    initHp();
}

void Boss::initHp()
{
    _hpBar.setSize(sf::Vector2f(_maxHp, 50.f));
    _hpBar.setFillColor(sf::Color::Red);
    _hpBar.setPosition((_windowX - _maxHp) * 0.5f, 5.f);
    _hpBar.setOutlineThickness(5.f);
    _hpBar.setOutlineColor(sf::Color::Black);
}

void Boss::update(const sf::Time &deltaTime)
{
    if (_isAlive)
    {
        _hpBar.setSize(sf::Vector2f(_hp, 50.f)); // Update the hp bar size dynamically
        randomMove(deltaTime); // Move the boss randomly
        attack(deltaTime);     // Implement attack logic here
    }
    for (auto it = _attacks.begin(); it != _attacks.end();)
    {
        it->update(deltaTime); // Update each attack
        if (!it->isActive())
        {
            it = _attacks.erase(it); // Remove inactive attacks
        }
        else
        {
            ++it;
        }
    }
}

void Boss::draw(sf::RenderWindow &window) const
{
    window.draw(_sprite);
    window.draw(_hpBar);
    for (const auto &attack : _attacks)
    {
        attack.draw(window); // Draw each attack
    }
}

float Boss::getHp() const { return _hp; }

void Boss::randomMove(const sf::Time &deltaTime)
{
    const float step = _speed * deltaTime.asSeconds();
    sf::FloatRect bounds = _sprite.getGlobalBounds();
    sf::Vector2f position = _sprite.getPosition();

    if (position.x + bounds.width >= _windowX || position.x - bounds.width <= 0.f)
    {
        _direction *= -1.f; // Reverse direction
    }
    else if (std::rand() % 100 < 1) // 1% chance to change direction
    {
        _direction = (std::rand() % 2 == 0) ? 1.f : -1.f; // Randomize up or down
    }

    _sprite.move(_direction * step, 0.0f); // Move the boss horizontally
}

void Boss::takeDamage(int damage)
{
    _hp -= damage;
    if (_hp <= 0)
    {
        _isAlive = false;
        _hp = 0; // Ensure hp doesn't go negative
    }
    _hpBar.setSize(sf::Vector2f(_hp, 50.f)); // Update the hp bar size
}

bool Boss::isAlive() const
{
    return _isAlive;
}

void Boss::attack(const sf::Time &deltaTime)
{
    if (_attackClock.getElapsedTime().asSeconds() >= _attackTime)
    {
        _attacks.emplace_back(_window); // Create a new attack
        _attackClock.restart();          // Restart the attack clock
    }  
}