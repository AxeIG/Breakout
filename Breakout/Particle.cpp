#include "Particle.h"
#include "CONSTANTS.h"

Particle::Particle()
{
	//setFillColor(sf::Color::White);
	setSize(sf::Vector2f(PARTICLE_SIZE, PARTICLE_SIZE));
	_alive = false;
	_colour = sf::Color::Black;
}

void Particle::initialize(sf::Vector2f size, sf::Vector2f pos, sf::Color color , sf::Vector2f dir  )
{
	setPosition(sf::Vector2f(pos));
	setSize(size);
	setDirection(dir);
	_alive = true;
	_clock = 0.0f;
	setFillColor(color);
	_colour = color;
	
}

void Particle::update(float dt)
{
	// Move Particle in assigned _direction
	_clock += dt;
	_alpha = _clock / PARTICLE_TIME_SPAN * 255;
	setFillColor(sf::Color(_colour.r, _colour.g, _colour.b, 255 - _alpha));
	move(_direction * dt * PARTICLE_SPEED);

	if (_clock >= PARTICLE_TIME_SPAN)
	{
		_alive = false;
	}
	
		
}

