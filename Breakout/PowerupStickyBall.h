#pragma once
#include "PowerupBase.h"
class PowerupStickyBall : public PowerupBase
{
public:
    PowerupStickyBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupStickyBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect

};

