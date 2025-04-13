#include "stateManager.hpp"

GameStateManager::GameStateManager() : currentState(GameState::Running)
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
}

void GameStateManager::update(sf::Time deltaTime)
{
    // 若有动画或者定时切换效果可以在此更新
}

void GameStateManager::draw(sf::RenderWindow &window)
{
    if (currentState == GameState::Victory)
    {
        window.draw(victorySprite);
    }
    else if (currentState == GameState::Defeat)
    {
        window.draw(defeatSprite);
    }
    // Running 状态下无需绘制额外内容
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


