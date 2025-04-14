#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet(const sf::Vector2f &startPos);
    void update(const sf::Time &deltaTime);
    void draw(sf::RenderWindow &window) const;

    bool isActive() const;
    sf::FloatRect collisionRect() const; // get the bounding box of the bullet
    void deactivate();

private:
    sf::CircleShape _bullet;
    // 存在 const 成员变量时，编译器无法生成默认的移动赋值运算符，std::vector 进行元素移动时失败
    float _speed = 1200.f; 
    float _radius = 15.f; // Bullet radius
    bool _isActive = true;
};
