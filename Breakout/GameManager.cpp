#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>
#include "ParticleManager.h"

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), 
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{

    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);

}

void GameManager::initialize()
{
    _paddle = new Paddle(_window);
    _ball = new Ball(_window, 400.0f, this);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ui = new UI(_window, _lives, this);

    PowerupManager::initialize(_window, _paddle, _ball);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = PowerupManager::getPowerupInEffect();
    _ui->updatePowerupScreenInfo(_powerupInEffect);
    _powerupInEffect.second -= dt;
    _mousePos = (sf::Mouse::getPosition(*_window));


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        _particle_manager.spawnParticles(sf::Vector2f(_mousePos), sf::Vector2f(-1,1),3);
    }
    

       
    if (_lives <= 0)
    {
        _masterText.setString("Game over.");
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.");
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
    {
        PowerupManager::spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);
   float x = sf::Mouse::getPosition(*_window).x;
   
    
   if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (_paddle->getBounds().contains(sf::Vector2f(_mousePos))))
   {
       if (_paddle->isDragged() == false)
       {
           _paddle->calculateMouseOffset(_mousePos.x);
           _paddle->setDragged(true);
       }
   }
   if (_paddle->isDragged())
   {
       _paddle->mouseDrag(_mousePos.x);
       if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        _paddle->setDragged(false);
   }
    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    PowerupManager::update(dt);
    ParticleManager::update(dt);
}

void ScreenShake(sf::RenderWindow* window, int duration, int intensity)
{
    int x, y;
    x = window->getPosition().x;
    y = window->getPosition().y;
    // ScreenShake
    for (int i = 0; i < duration; i++)
    {
        int rx = rand() % intensity - intensity/2;
        int ry = rand() % intensity - intensity / 2;
        window->setPosition(sf::Vector2i(x + rx, y + ry));

    }
    window->setPosition(sf::Vector2i(x, y));
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);
    ScreenShake(_window, 110, 50);
    
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    PowerupManager::render();
    _window->draw(_masterText);
    
    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
//PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
