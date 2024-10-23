#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

class Particle : public sf::RectangleShape
{
public:
	Particle();
	~Particle() {};

	void initialize(sf::Vector2f size, sf::Vector2f pos, sf::Color color = sf::Color::White, sf::Vector2f dir = sf::Vector2f(0,0) );
	void update(float dt);
	
	// setters and getters
	void setAlive(bool val) { _alive = val; }
	void setDirection(sf::Vector2f dir) { _direction = dir; }
	void setDirection(float x, float y) { _direction = sf::Vector2f(x, y); }

	bool isAlive() { return _alive; }
	sf::Vector2f getDirection() { return _direction; }
	float getClock() { return _clock; }

private:

	bool _alive;
	sf::Vector2f _direction;
	float _alpha;
	float _clock;
	sf::Color _colour;

};

