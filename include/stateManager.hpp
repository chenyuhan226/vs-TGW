#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class GameState
{
    Start,   // State before the game starts
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
    // Textures and Sprites
    sf::Texture victoryTexture;
    sf::Sprite victorySprite;
    sf::Texture defeatTexture;
    sf::Sprite defeatSprite;

    // Text
    sf::Font font;
    sf::Text startText;
    sf::Text infoText;
    sf::Text authorText;

    // 加载胜利/失败资源
    void loadResources();
};
