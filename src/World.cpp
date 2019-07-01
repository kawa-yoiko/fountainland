#include "World.h"

World::World(){
	b2Vec2 gravity;
	gravity.Set(0.0f, 10.0f);
	m_world = new b2World(gravity);
}

World::~World(){
	for (auto&& it : interactableList)
		delete(it);
	delete _player;
	delete m_world;
}

void World::addWindmill(Windmill* windmill){
	windmill->m_world = this->m_world;
	windmill->addToWorld();
	interactableList.push_back(windmill);
}

void World::addBubble(Bubble* bubble){
	bubble->m_world = this->m_world;
	bubble->putIntoWorld();
	interactableList.push_back(bubble);
}

void World::addFountain(Fountain* fountain){
	fountain->m_world = this->m_world;
	fountain->drawFountain();
	fountain->emitWater();
	interactableList.push_back(fountain);
}

void World::addCloud(Cloud* cloud){
	cloud->m_world = this->m_world;
	const b2ParticleSystemDef particleSystemDef;
	cloud->m_particleSystem = m_world->CreateParticleSystem(&particleSystemDef);
	cloud->m_particleSystem->SetRadius(3.5f);
	cloud->putIntoWorld();
	interactableList.push_back(cloud);
}

void World::addPlayer(Player* player){
	player->m_world = this->m_world;
	const b2ParticleSystemDef particleSystemDef;
	player->m_particleSystem = m_world->CreateParticleSystem(&particleSystemDef);
	player->m_particleSystem->SetRadius(0.035f);
	player->addToWorld();
	_player = player;
}

void World::addGround(Ground* ground){
	ground->m_world = this->m_world;
	ground->addToWorld();
	interactableList.push_back(ground);
}

void World::tick(){
	float32 hz = 60.0f;
	float32 timeStep = 1.0f / hz;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;
	int32 particleIterations = b2CalculateParticleIterations(10, 0.04f, 1 / hz);
	for (auto&& it : interactableList)
		it->beforeTick();
	m_world->Step(timeStep, velocityIterations, positionIterations, particleIterations);
}
