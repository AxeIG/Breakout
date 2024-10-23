#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies
#include "ParticleManager.h"

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1})
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);

    _stuck_point = 0;

}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    ParticleManager::spawnTrailParticle(sf::Vector2f(_sprite.getPosition().x + BALL_RADIUS / 2,
        _sprite.getPosition().y + BALL_RADIUS / 2),
        _sprite.getFillColor());

    // check for powerup, tick down or correct
    if (_timeWithPowerupEffect > 0.f)
    {
        _timeWithPowerupEffect -= dt;
    }
    else
    {
        if (_velocity != VELOCITY)
            _velocity = VELOCITY;   // reset speed.
        else
        {
            setFireBall(0);    // disable fireball
            _sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
        }        
    }

    // Fireball effect
    if (_isFireBall)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        _sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }
    else if (_isStickyBall)
    {
        _sprite.setFillColor(stickyBallEffect);
    }
   

    // Update position with a subtle floating-point error 
    if(!_isStuck)
        _sprite.move(_direction * _velocity * dt);

    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2u windowDimensions = _window->getSize();

    // bounce on walls
    if ((position.x >= windowDimensions.x - 2 * RADIUS && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
    }
    

    // lose life bounce
    if (position.y > windowDimensions.y)
    {
        _sprite.setPosition(0, 300);
        _direction = { 1, 1 };
        _gameManager->loseLife();
    }
    sf::Vector2f points = sf::Vector2f(0, 0);

    // Stickyball effect
    if ((_isStickyBall) && (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds())))
    {
        sf::Vector2f paddle_pos = _gameManager->getPaddle()->getBounds().getPosition();
        _sprite.setFillColor(stickyBallEffect);
        if (!_isStuck)
        {
            // Find position of the ball on paddle
            _stuck_point = _sprite.getGlobalBounds().getPosition().x - paddle_pos.x;
            _gameManager->getPaddle()->setFillColour(stickyBallEffect);
            _isStuck = true;
        }
        _sprite.setPosition(sf::Vector2f(paddle_pos.x + _stuck_point, _sprite.getGlobalBounds().getPosition().y));

        // Launch Ball Upwards
        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
        {
            _direction = sf::Vector2f(0, -1);
            _sprite.move(sf::Vector2f(0, -1 * BALL_SPEED * dt)); 
            _isStuck = false;
            _isStickyBall = false;
            _gameManager->getPaddle()->setFillColour(_gameManager->getPaddle()->getColour());
            PowerupManager::setPowerupInEffect(0.0f);
        }

    }
    else if(!_isStuck)
    {

        // collision with paddle
        if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
        {
            _direction.y *= -1; // Bounce vertically

            float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
            _direction.x = paddlePositionProportion * 2.0f - 1.0f;

            // Adjust position to avoid getting stuck inside the paddle
            _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * RADIUS);
            
            ParticleManager::spawnParticles(_sprite.getPosition(), sf::Vector2f(_direction.x * -1, _direction.y * -1), NUMBER_OF_PARTICLES);
        }

        // collision with bricks
        int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);

        if (_isFireBall) return; // no collisisons when in fireBall mode.
        if (collisionResponse == 1)
        {
            _direction.x *= -1; // Bounce horizontally
        }
        else if (collisionResponse == 2)
        {
            _direction.y *= -1; // Bounce vertically
        }

    }

}

void Ball::render()
{
    ParticleManager::render(_window);
    _window->draw(_sprite);
}

void Ball::setVelocity(float coeff, float duration)
{
    _velocity = coeff * VELOCITY;
    _timeWithPowerupEffect = duration;
}

void Ball::setFireBall(float duration)
{
    if (duration) 
    {
        _isFireBall = true;
        _timeWithPowerupEffect = duration;        
        return;
    }
    _isFireBall = false;
    _timeWithPowerupEffect = 0.f;    
}

void Ball::setStickyBall(bool val)
{
    _isStickyBall = val ;

}

sf::FloatRect Ball::getBounds()
{
    return _sprite.getGlobalBounds();
}


