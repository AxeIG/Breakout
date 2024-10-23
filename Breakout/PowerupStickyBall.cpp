#include "PowerupStickyBall.h"

PowerupStickyBall::PowerupStickyBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball):
	PowerupBase(window,paddle,ball)
{
	_sprite.setFillColor(stickyBallEffect);

}

PowerupStickyBall::~PowerupStickyBall()
{
}

std::pair<POWERUPS, float> PowerupStickyBall::applyEffect()
{
	_ball->setStickyBall(true);
	return { stickyBall, 100.0f };
}
