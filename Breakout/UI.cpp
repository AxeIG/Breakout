#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>

UI::UI(sf::RenderWindow* window, int lives, GameManager* gameManager) 
	: _window(window), _gameManager(gameManager)
{
	for (int i = lives; i > 0; --i)
	{
		sf::CircleShape newLife;
		newLife.setFillColor(sf::Color::Red);	
		newLife.setOutlineColor(sf::Color::Cyan);
		newLife.setOutlineThickness(4.0f);
		newLife.setRadius(LIFE_RADIUS);
		newLife.setPosition((LIFE_RADIUS*2 + LIFE_PADDING) * i, LIFE_PADDING);
		_lives.push_back(newLife);
	}
	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(800, 10);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);

	_progressBar.setPosition(752, 56);
	//_progressBar.setSize(sf::Vector2f(200, 20));
	_progressBar.setFillColor(sf::Color::Green);

	_progressBorder.setPosition(748, 52);
	_progressBorder.setSize(sf::Vector2f(208, 28));
	_progressBorder.setFillColor(sf::Color(236, 236, 236));
	


}

UI::~UI()
{
}


void UI::updatePowerupScreenInfo(std::pair<POWERUPS, float> powerup)
{
	std::ostringstream oss;

	switch (powerup.first)
	{
	case bigPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("big " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		_progressBar.setSize(sf::Vector2f(powerup.second / 5.0f * 200, 20));
		_progressBar.setFillColor(paddleEffectsColour);

		break;
	case smallPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("small " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		_progressBar.setSize(sf::Vector2f(powerup.second / 5.0f * 200, 20));
		_progressBar.setFillColor(paddleEffectsColour);

		break;
	case slowBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("slow " + oss.str());
		_powerupText.setFillColor(speedEffectColour);
		_progressBar.setSize(sf::Vector2f(powerup.second / 5.0f * 200, 20));
		_progressBar.setFillColor(speedEffectColour);

		break;
	case fastBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fast " + oss.str());
		_powerupText.setFillColor(speedEffectColour);
		_progressBar.setSize(sf::Vector2f(powerup.second / 5.0f * 200, 20));
		_progressBar.setFillColor(speedEffectColour);

		break;
	case fireBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fire " + oss.str());
		_powerupText.setFillColor(fireballEffectColour);
		_progressBar.setSize(sf::Vector2f(powerup.second / 5.0f * 200, 20));
		_progressBar.setFillColor(fireballEffectColour);

		break;
	case none:
		//_progressBorder.isdead
		_powerupText.setString("");
		_progressBar.setSize(sf::Vector2f(0, 0));
		
		break;
	}
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	_window->draw(_powerupText);
	if (_progressBar.getSize().x != 0)
	{
		_window->draw(_progressBorder);
		_window->draw(_progressBar);
	}


	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}