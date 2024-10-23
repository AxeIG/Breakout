#pragma once
#include "Particle.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "CONSTANTS.h"
#include <vector>
class ParticleManager
{
public:
	ParticleManager() {}
	~ParticleManager() { 
		_particles.clear();
		_trail.clear();
	}

	static void spawnParticles(sf::Vector2f pos, sf::Vector2f dir, int spawn_number);
	static void spawnTrailParticle(sf::Vector2f pos, sf::Color colour);
	static void update(float dt);
	static void render(sf::RenderWindow* window);


private:

	static std::vector<Particle*> _particles;
	static std::vector<Particle*> _trail;


};

