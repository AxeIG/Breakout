#include "ParticleManager.h"
#include <random>

std::random_device rd;  // Random device for seeding
std::mt19937 gen(rd()); // Mersenne Twister engine seeded with random device

std::vector<Particle*> ParticleManager::_particles;
std::vector<Particle*> ParticleManager::_trail;

void ParticleManager::spawnParticles(sf::Vector2f pos, sf::Vector2f dir, int spawn_number)
{

	for (int i = 0; i < NUMBER_OF_PARTICLES; i++)
	{
		Particle* particle = new Particle();
		std::uniform_int_distribution<int> offsetDist(-PARTICLE_OFFSET, PARTICLE_OFFSET); // For position offsets
		int r = offsetDist(gen);
		int R = offsetDist(gen);

		sf::Vector2f particle_size = sf::Vector2f(PARTICLE_SIZE, PARTICLE_SIZE);
		particle->initialize(particle_size, sf::Vector2f(pos.x + r, pos.y + R),sf::Color::White ,dir);
		_particles.push_back(particle);
	}
	
}

void ParticleManager::spawnTrailParticle(sf::Vector2f pos, sf::Color colour)
{
	Particle* particle = new Particle();
	sf::Vector2f trail_size = sf::Vector2f(TRAIL_SIZE, TRAIL_SIZE);

	particle->initialize(trail_size, pos, colour);

	_trail.push_back(particle);
}

void ParticleManager::update(float dt)
{
	for (auto p : _particles)
	{
		if (p->isAlive())
			p->update(dt);
	}
	for (auto p : _trail)
	{
		if (p->isAlive())
		{
			p->update(dt);
		}
	}

	
}

void ParticleManager::render(sf::RenderWindow* window)
{
	for (auto p:_particles)
	{
		if (p->isAlive()) 
		{
			window->draw(*p);
		}
	}

	for (auto p : _trail)
	{
		if (p->isAlive())
		{
			window->draw(*p);
		}
	}
}

