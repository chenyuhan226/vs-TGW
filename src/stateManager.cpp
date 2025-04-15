#include "stateManager.hpp"

GameStateManager::GameStateManager() : currentState(GameState::Start)
{
    loadResources();
}

void GameStateManager::setState(GameState newState)
{
    currentState = newState;
}

GameState GameStateManager::getState() const
{
    return currentState;
}

void GameStateManager::loadResources()
{
    if (!victoryTexture.loadFromFile("data/victory.png"))
    {
        std::cerr << "Failed to load victory image!" << std::endl;
    }
    victorySprite.setTexture(victoryTexture);
    // 设置胜利图片居中显示并调整大小（假设窗口大小已知，可以后续动态更新）
    resize(victorySprite, sf::Vector2u(2400, 1300)); // 假设窗口大小为2400x1300

    if (!defeatTexture.loadFromFile("data/defeat.png"))
    {
        std::cerr << "Failed to load defeat image!" << std::endl;
    }
    defeatSprite.setTexture(defeatTexture);
    resize(defeatSprite, sf::Vector2u(2400, 1300)); // 假设窗口大小为2400x1300

    // load font and set text properties
    if (!font.loadFromFile("data/arial_mt.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
    }
    startText.setFont(font);
    startText.setString("Press Enter to Start");
    startText.setCharacterSize(150);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(500, 500); // Set position as needed
    infoText.setFont(font);
    infoText.setString("WASD   : Move\nJ            : Shoot\nEsc       : Exit");
    infoText.setCharacterSize(50);
    infoText.setPosition(50, 1100); // Set position as needed
    infoText.setFillColor(sf::Color::Black);
    authorText.setFont(font);
    authorText.setString("Author: coldrain226\nVersion: 0.1.1");
    authorText.setCharacterSize(30);
    authorText.setPosition(2050, 1200); // Set position as needed
    authorText.setFillColor(sf::Color::Black);
}

void GameStateManager::update(sf::Time deltaTime)
{
    // 若有动画或者定时切换效果可以在此更新
}

void GameStateManager::draw(sf::RenderWindow &window)
{
    switch (currentState) {
        case GameState::Start:
            window.draw(startText);
            window.draw(infoText);
            window.draw(authorText);
            break;
        case GameState::Victory:
            window.draw(victorySprite);
            break;
        case GameState::Defeat:
            window.draw(defeatSprite);
            break;
        default:
            break;
    }
    // Running state does not draw anything else
}

// Resize the sprite to fit the new window size
void GameStateManager::resize(sf::Sprite &sprite, const sf::Vector2u &newSize)
{
    // 获取纹理原始尺寸
    const auto textureSize = sprite.getTexture()->getSize();

    // 计算水平和垂直方向缩放比例
    const float scaleX = static_cast<float>(newSize.x) / textureSize.x;
    const float scaleY = static_cast<float>(newSize.y) / textureSize.y;

    // 使用较小的比例，以确保图像完全显示在目标尺寸内（保持比例）
    const float uniformScale = std::min(scaleX, scaleY);

    // 应用统一缩放比例
    sprite.setScale(uniformScale, uniformScale);

    // 如果需要居中，可进一步调整 sprite 的位置，比如：
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float posX = (newSize.x - bounds.width) / 2.f;
    float posY = (newSize.y - bounds.height) / 2.f;
    sprite.setPosition(posX, posY);
}


