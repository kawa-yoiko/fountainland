#include "World.h"

World::World() : _width(80) {
	b2Vec2 gravity;
	gravity.Set(0.0f, 10.0f);
	m_world = new b2World(gravity);
	b2ParticleSystemDef particleSystemDef;
	//Alter the elastic strength here.
	particleSystemDef.elasticStrength = 1.2f;
	m_particleSystem = m_world->CreateParticleSystem(&particleSystemDef);
	m_particleSystem->SetRadius(0.25f);
}

World::~World(){
	for (auto&& it : interactableList)
		if(it)
			delete(it);
	if(_player)
		delete _player;
	if(m_world)
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
	fountain->m_particleSystem = this->m_particleSystem;
	interactableList.push_back(fountain);
}

void World::addCloud(Cloud* cloud){
	cloud->m_world = this->m_world;
	cloud->m_particleSystem = this->m_particleSystem;
	cloud->putIntoWorld();
	interactableList.push_back(cloud);
}

void World::addPlayer(Player* player){
	player->m_world = this->m_world;
	player->m_particleSystem = this->m_particleSystem;
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
