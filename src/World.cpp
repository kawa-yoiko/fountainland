#include "World.h"

World::World(){
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	m_world = new b2World(gravity);
}

void World::addWindmill(Windmill& windmill){
	windmill.m_world = this->m_world;
	windmill.addToWorld();
}

void World::addBubble(Bubble& bubble){
	bubble.m_world = this->m_world;
	bubble.putIntoWorld();
}

void World::addFountain(Fountain& fountain){
	fountain.m_world = this->m_world;
	fountain.drawFountain();
	fountain.emitWater();
}

void World::addCloud(Cloud& cloud){
	cloud.m_world = this->m_world;
	cloud.putIntoWorld();
}

void World::addPlayer(Player& player){
	player.m_world = this->m_world;
	const b2ParticleSystemDef particleSystemDef;
	player.m_particleSystem = m_world->CreateParticleSystem(&particleSystemDef);
	player.addToWorld();
}

void World::tick(){
	float32 hz = 60.0f;
	float32 timeStep = 1.0f / hz;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;
	int32 particleIterations = b2CalculateParticleIterations(10, 0.04f, 1 / hz);
	m_world->Step(timeStep, velocityIterations, positionIterations, particleIterations);
}
