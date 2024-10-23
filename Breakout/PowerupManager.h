#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "PowerupBase.h"
#include "PowerupBigPaddle.h"
#include "PowerupSmallPaddle.h"
#include "PowerupSlowBall.h"
#include "PowerupFastBall.h"
#include "PowerupFireBall.h"
#include "PowerupStickyBall.h"
#include "Paddle.h"
#include "Ball.h"


class PowerupManager
{
public:
    PowerupManager();
    ~PowerupManager();
    static void initialize(sf::RenderWindow* window, Paddle* paddle, Ball* ball); // Initialize static variables
    static void cleanup(); // Clean up dynamically allocated memory
    static void update(float dt);
    static void render();
    static void spawnPowerup(); // Method to spawnParticle a power-up
    static void checkCollision(); // Check collision with paddle
    static int getPowerupsSpawned();
    static std::pair<POWERUPS, float> getPowerupInEffect();
    static void setPowerupInEffect(float second);

private:
    static sf::RenderWindow* _window;
    static Paddle* _paddle;
    static Ball* _ball;
    static std::vector<PowerupBase*> _powerups;  // Used to manage deletion.
    static std::optional<std::pair<POWERUPS, float>> _powerupInEffect; // Used for GameManager to get reference.
    static sf::RectangleShape _timerBar;
};