#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdexcept>
#include "player.hpp"
#include "boss.hpp" 
#include "soundManager.hpp" // Include the SoundManager header
#include "stateManager.hpp" // Include the GameStateManager header
#include <memory> // For std::unique_ptr

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();     // 处理SFML事件
    void update(sf::Time dt); // 更新游戏状态
    void draw();            // 绘制画面

    sf::RenderWindow _window;
    Player _player;
    Boss _boss;
    std::unique_ptr<SoundManager> _soundManager; // 声音管理器
    GameStateManager _stateManager;
    bool _bossSkillUsed = false; // boss_skill used flag
    bool _bossHighUsed = false; // boss_high used flag
};
