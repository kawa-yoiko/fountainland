#include "Cloud.h"

Cloud::Cloud() {
	type = Type::Cloud;
}

Cloud::~Cloud(){
	if(m_particleSystem)
		m_world->DestroyParticleSystem(m_particleSystem);
}

void Cloud::putIntoWorld()
{
	const float32 length = 40.0f, width = 20.0f;
	b2Vec2 pos(getPosition().x, getPosition().y);
	double cloudAngle = getAngle();

	b2World* world = getWorld();
	b2ParticleSystem* particleSystem = getParticleSystem();
	//should differ the cloud particle system and the player particle system
	//cloudParticleSystemDef.elasticStrength = 1.0f
	b2PolygonShape shape;
	shape.SetAsBox(length, width, pos, cloudAngle);

	b2ParticleGroupDef pd;
	pd.flags = b2_springParticle;
	pd.groupFlags = b2_solidParticleGroup;
	pd.position.Set(pos.x, pos.y);
	pd.shape = &shape;
//	pd.color.Set(0, 0, 255, 255);
	particleSystem->CreateParticleGroup(pd);

	//this should not affect the player
	particleSystem->SetGravityScale(0);
	
}

//this should be done every step in the world
void Cloud::beforeTick() {
	for (int i = 0; i < m_particleSystem->GetParticleCount(); ++i) {
		m_particleSystem->GetVelocityBuffer()[i] = b2Vec2_zero;
	}
}