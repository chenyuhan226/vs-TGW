#include "player.hpp"

Player::Player(const sf::RenderWindow &window) : _window(window)
{
    if (!_texture.loadFromFile("data/saki.png"))
        throw std::runtime_error("Failed to load player image!");
    _sprite.setTexture(_texture);
    _texture.setSmooth(true);
    _sprite.setScale(0.7f, 0.7f); // change the size of the player sprite
    _sprite.setOrigin(_texture.getSize().x * 0.5f, _texture.getSize().y * 0.5f);
    _sprite.setPosition(_window.getSize().x * 0.5, _window.getSize().y - _sprite.getGlobalBounds().height);
    initHp();
}

void Player::initHp()
{
    _hpBar.setSize(sf::Vector2f(_initialHpBarWidth, 50.f));
    _hpBar.setFillColor(sf::Color(0x77, 0x99, 0xCC, 0xFF));
    _hpBar.setPosition(5.f, _window.getSize().y - 55.f);
    _hpBar.setOutlineThickness(5.f);
    _hpBar.setOutlineColor(sf::Color::Black);
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
    cleanupBullets();
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

float Player::getHp() const
{
    return _hp; // Return the current HP
}
void Player::takeDamage(int damage)
{
    _hp -= damage;
    if (_hp < 0)
        _hp = 0; // Ensure HP doesn't go below 0
    // Update the HP bar
    float newWidth = _initialHpBarWidth * (_hp / _maxHp);
    newWidth = std::max(0.f, newWidth); // Ensure width doesn't go below 0
    _hpBar.setSize(sf::Vector2f(newWidth, _hpBar.getSize().y));
}

bool Player::isAlive() const
{
    return _hp > 0; // Return true if the player is alive
}

sf::FloatRect Player::collisionRect() const
{
    return _sprite.getGlobalBounds(); // Return the player's collision rectangle
}
std::vector<Bullet> &Player::getBullets()
{
    return _bullets; // Return the vector of bullets
}
void Player::cleanupBullets()
{
    _bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(),
                                  [](const Bullet &b)
                                  { return !b.isActive(); }),
                   _bullets.end()); // Remove inactive bullets from the vector
}