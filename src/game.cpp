#include "game.hpp"

Game::Game()
    : _window(sf::VideoMode(2400, 1300), "vs TGW"), _player(_window), _boss(_window),
      _stateManager() // Initialize the state manager (Start state)
{
    _window.setFramerateLimit(60);
    _window.setPosition(sf::Vector2i(50, 50));
    // intialize SoundManager
    _soundManager = std::make_unique<SoundManager>();
    _soundManager->loadSound("boss_start", "data/boss_start.wav");
    _soundManager->loadSound("boss_high", "data/boss_high.wav");
    _soundManager->loadSound("boss_skill", "data/boss_skill.wav");
    _soundManager->loadSound("victory", "data/victory.wav");
    _soundManager->loadSound("defeat", "data/defeat.wav");
}

void Game::run()
{
    sf::Clock clock;
    while (_window.isOpen())
    {
        sf::Time dt = clock.restart();
        processEvents();
        update(dt);
        draw();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            _window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            _window.close();
        if (_stateManager.getState() == GameState::Start && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        {
            // Start the game when Enter is pressed
            _stateManager.setState(GameState::Running); 
            _soundManager->playSound("boss_start"); // Play start sound
        }
    }
}
void Game::update(sf::Time dt)
{
    if (_stateManager.getState() == GameState::Running)
    {

        _player.handleInput(dt);
        _player.update(dt);
        _boss.update(dt); // Update boss if needed

        // Check collisions between player bullets and boss
        for (auto &bullet : _player.getBullets())
        {
            if (bullet.isActive() && bullet.collisionRect().intersects(_boss.collisionRect()))
            {
                _boss.takeDamage(4); // the max boss hp is 100
                bullet.deactivate();  // Deactivate the bullet after collision
            }
        }
        // Check collisions between boss attack and player
        for (auto &attack : _boss.getAttacks())
        {
            if (attack.isActive() && attack.collisionRect().intersects(_player.collisionRect()))
            {
                _player.takeDamage(1);
                attack.deactivate(); // Deactivate the attack after collision
            }
        }

        if (_boss.getHp() <= 50 && !_bossHighUsed)
        {
            _bossHighUsed = true; // Set the flag to true to prevent multiple activations
            _soundManager->playSound("boss_high");
            _boss.setAttackTime(0.3f); // Increase attack frequency
        }
        if (_boss.getHp() <= 20 && !_bossSkillUsed)
        {
            _bossSkillUsed = true; // Set the flag to true to prevent multiple activations
            _soundManager->playSound("boss_skill");
        }
        // Victory and defeat conditions
        if (_boss.getHp() <= 0)
        {
            _stateManager.setState(GameState::Victory);
            _soundManager->playSound("victory"); 
        }
        if (_player.getHp() <= 0)
        {
            _stateManager.setState(GameState::Defeat);
            _soundManager->playSound("defeat"); 
        }
    }
}
void Game::draw()
{
    _window.clear(sf::Color::White);
    if (_boss.getHp() <= 20)
    {// Dark gray background when boss HP is low
        _window.clear(sf::Color(20, 20, 20)); 
    }
    // 绘制游戏主体：在 Running 状态下显示游戏内容
    if (_stateManager.getState() == GameState::Running)
    {
        _player.draw(_window);
        _boss.draw(_window);
    }
    else // 在游戏结束状态下，将胜利或失败图片覆盖绘制
    {
        _stateManager.draw(_window);
    }

    _window.display();
}
