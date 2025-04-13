#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdexcept>
#include "player.hpp"
// #include "boss.hpp" 

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
    // Boss boss;
    // ...其他成员
};
