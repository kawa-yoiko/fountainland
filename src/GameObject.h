#pragma once
#include "raylib.h"
#include "Box2D/Box2D.h"

class GameObject {
public:
	virtual ~GameObject() = 0;
	GameObject();

	//Tell whether the game object is player or not
	bool isPlayer;
	b2World* getWorld() { return m_world; }
	b2ParticleSystem* getParticleSystem() { return m_particleSystem; }

	b2World* m_world;
	b2ParticleSystem* m_particleSystem;
};
