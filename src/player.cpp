#include "player.hpp"

Player::Player(const sf::RenderWindow& window) : _window(window)
{
    if (!_texture.loadFromFile("data/saki.png"))
        throw std::runtime_error("Failed to load player image!");
    _sprite.setTexture(_texture);
    _texture.setSmooth(true);
    _sprite.setScale(0.2f, 0.2f); // Scale down the sprite to make it smaller
    _sprite.setOrigin(_texture.getSize().x * 0.5f, _texture.getSize().y * 0.5f);
    _sprite.setPosition(_window.getSize().x*0.5, _window.getSize().y - _sprite.getGlobalBounds().height);
    initHp();
}

void Player::initHp()
{
    _hpBar.setSize(sf::Vector2f(300.f, 50.f));
    _hpBar.setFillColor(sf::Color(0x77, 0x99, 0xCC, 0xFF));
    _hpBar.setPosition(0.f, _window.getSize().y - 100.f);
}

void Player::shoot(const sf::Time &deltaTime)
{
    if (_shootClock.getElapsedTime().asSeconds() >= _shootCooldown) // Adjust the shooting interval as needed
    {

        sf::Vector2f bulletPosition = _sprite.getPosition() + sf::Vector2f(0.f, -_sprite.getGlobalBounds().height * 0.5f);
        _bullets.emplace_back(bulletPosition); // Create a new bullet at the player's position
        _shootClock.restart();                 // Restart the shoot clock
    }
}

void Player::handleInput(const sf::Time &deltaTime)
{
    const float step = _speed * deltaTime.asSeconds();
    sf::FloatRect bounds = _sprite.getGlobalBounds();
    sf::Vector2f position = _sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (position.y - bounds.height / 2.f) > 0.f)
    {
        _sprite.move(0.0f, -step);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (position.x - bounds.width / 2.f) > 0.f)
    {
        _sprite.move(-step, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (position.y + bounds.height / 2.f) < _window.getSize().y)
    {
        _sprite.move(0.0f, step);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (position.x + bounds.width / 2.f) < _window.getSize().x)
    {
        _sprite.move(step, 0.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
    {
        shoot(deltaTime); // Call the shoot function when 'J' is pressed
    }
}

void Player::update(const sf::Time &deltaTime)
{
    for (auto &bullet : _bullets)
    {
        bullet.update(deltaTime); // Update each bullet
    }
    // Remove inactive bullets
    for (auto it = _bullets.begin(); it != _bullets.end();)
    {
        if (!it->isActive())
        {
            it = _bullets.erase(it); // Remove inactive bullets
        }
        else
        {
            ++it;
        }
    }
    // Update the HP bar
    _hpBar.setSize(sf::Vector2f(_hpBar.getSize().x * (_hp / static_cast<float>(_maxHp)), _hpBar.getSize().x));
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(_sprite);
    window.draw(_hpBar);
    for (const auto &bullet : _bullets)
    {
        bullet.draw(window); // Draw each bullet
    }
}

void Player::takeDamage(int damage)
{
    _hp -= damage;
    if (_hp < 0)
        _hp = 0; // Ensure HP doesn't go below 0
}

bool Player::isAlive() const
{
    return _hp > 0; // Return true if the player is alive
}
