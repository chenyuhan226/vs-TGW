#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <algorithm>
#include "bossAttack.hpp"

class Boss{
public:
    explicit Boss(const sf::RenderWindow& window);
    void update(const sf::Time& deltaTime);
    void draw(sf::RenderWindow& window) const;
    
    float getHp() const;
    void randomMove(const sf::Time& deltaTime);
    void takeDamage(int damage);
    bool isAlive() const;
    sf::FloatRect collisionRect() const; // Return the collision rectangle
    std::vector<BossAttack>& getAttacks(); // Return the vector of attacks
    void cleanupAttacks(); // Remove inactive attacks from the vector
    void setAttackTime(float attackTime); // Set the attack time
    
private:
    void initHp();
    void attack(const sf::Time& deltaTime);
    void computeParameters();

    const sf::RenderWindow& _window;
    const float _windowX;
    const float _windowY;

    std::vector<BossAttack> _attacks;
    float _attackTime = 0.5f; // time between attacks
    sf::Clock _attackClock;

    sf::Sprite _sprite;
    sf::Texture _texture;

    sf::RectangleShape _hpBar;
    float _hp = 100.f; // will be set to hpBar size
    const float _maxHp = 100.f; // will be set to hpBar size
    const float _initialHpBarWidth = 2000.f; // will be set to hpBar size

    float _direction = 1.f; // 1 for right, -1 for left
    const float _speed = 200.f;
    bool _isAlive = true;
};