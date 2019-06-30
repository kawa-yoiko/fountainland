#pragma once
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Particle/b2ParticleGroup.h"
#include "Windmill.h"
#include "Bubble.h"
#include "Cloud.h"
#include "Fountain.h"
#include "Player.h"

class World {
public:
	World();
	b2World* m_world;

	void addWindmill(Windmill& windmill);
	void addBubble(Bubble& bubble);
	void addFountain(Fountain& fountain);
	void addCloud(Cloud& cloud);
	void addPlayer(Player& player);
	void tick();
	
};