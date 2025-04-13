#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class GameState
{
    Running,
    Victory,
    Defeat
};

class GameStateManager
{
public:
    GameStateManager();
    void setState(GameState newState);
    GameState getState() const;
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow &window);

    void resize(sf::Sprite &sprite, const sf::Vector2u &newSize);

private:
    GameState currentState;
    // 状态对应的图片及精灵
    sf::Texture victoryTexture;
    sf::Sprite victorySprite;
    sf::Texture defeatTexture;
    sf::Sprite defeatSprite;

    // 加载胜利/失败资源
    void loadResources();
};
