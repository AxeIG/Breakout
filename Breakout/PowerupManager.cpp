#include "PowerupManager.h"

sf::RenderWindow* PowerupManager::_window = nullptr;
Paddle* PowerupManager::_paddle = nullptr;
Ball* PowerupManager::_ball = nullptr;
std::vector<PowerupBase*> PowerupManager::_powerups;
std::optional<std::pair<POWERUPS, float>> PowerupManager::_powerupInEffect = std::nullopt;
sf::RectangleShape PowerupManager::_timerBar;

PowerupManager::PowerupManager()
{
}

PowerupManager::~PowerupManager()
{
    for (auto powerup : _powerups)
    {
        delete powerup;
    }
    _powerups.clear();
}

void PowerupManager::initialize(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
{
    _window = window;
    _paddle = paddle;
    _ball = ball;
    _timerBar = sf::RectangleShape(sf::Vector2f(100.f, 10.f)); // Example size
}

void PowerupManager::update(float dt)
{
    // tick down powerup effect time. Reset if elapsed.
    if (_powerupInEffect)
    {
        _powerupInEffect->second -= dt;
        if (_powerupInEffect->second <= 0)
        {
            _powerupInEffect.reset();
        }
    }


    for (auto it = _powerups.begin(); it != _powerups.end(); )
    {
        checkCollision();
        
        // Delete powerups queued for removal
        (*it)->update(dt);
        if (!(*it)->isAlive())
        {
            delete* it;
            it = _powerups.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void PowerupManager::render()
{
    for (auto& powerup : _powerups)
    {
        powerup->render();
    }
}

void PowerupManager::spawnPowerup()
{
    //// TODO finish this.
    //switch (rand() % 5)
    //{
    //case 0:
    //    _powerups.push_back(new PowerupBigPaddle(_window, _paddle, _ball));
    //    break;
    //case 1:
    //    _powerups.push_back(new PowerupSlowBall(_window, _paddle, _ball));
    //    break;
    //case 2:
    //    _powerups.push_back(new PowerupFastBall(_window, _paddle, _ball));
    //    break;
    //case 3:
    //    _powerups.push_back(new PowerupSmallPaddle(_window, _paddle, _ball));
    //    break;
    //case 4:
    //    _powerups.push_back(new PowerupFireBall(_window, _paddle, _ball));
    //    break;
    //case 5:
    //    _powerups.push_back(new PowerupStickyBall(_window, _paddle, _ball));
    //case6:
    //    break;
    //}

    // TODO finish this.
    switch (rand() % 5)
    {
    case 0:
        _powerups.push_back(new PowerupStickyBall(_window, _paddle, _ball));
        break;
    case 1:
        _powerups.push_back(new PowerupStickyBall(_window, _paddle, _ball));
        break;
    case 2:
        _powerups.push_back(new PowerupStickyBall(_window, _paddle, _ball));
        break;
    case 3:
        _powerups.push_back(new PowerupStickyBall(_window, _paddle, _ball));
        break;
    case 4:
        _powerups.push_back(new PowerupStickyBall(_window, _paddle, _ball));
        break;
    case 5:
        _powerups.push_back(new PowerupStickyBall(_window, _paddle, _ball));
    case6:
        break;
    }
}

void PowerupManager::checkCollision()
{
    for (auto& powerup : _powerups)
    {

        if (powerup->checkCollisionWithPaddle())
        {
            _powerupInEffect = powerup->applyEffect();
           // powerup->setAlive(false);
        }
    }
}

int PowerupManager::getPowerupsSpawned()
{
    return _powerups.size();
}

std::pair<POWERUPS, float> PowerupManager::getPowerupInEffect()
{
    if (!_powerupInEffect) return { none, 0.f };
    return *_powerupInEffect;
}

// Change float value of power up
void PowerupManager::setPowerupInEffect(float second)
{
    if (_powerupInEffect) {
        _powerupInEffect->second = second; // Set time if the optional has a value
    }
}

