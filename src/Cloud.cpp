#include "Cloud.h"

Cloud::Cloud() {
	type = Type::Cloud;
}

Cloud::~Cloud(){
}

void Cloud::putIntoWorld()
{
	float32 length = size.x, width = size.y;
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
	pd.position.Set(0, 0);
	pd.shape = &shape;
//	pd.color.Set(0, 0, 255, 255);
	_cloudGroup=particleSystem->CreateParticleGroup(pd);
	
	_particleSys = particleSystem;
}

//this should be done every step in the world
void Cloud::beforeTick() {
	b2Vec2 gravity(0.0f, -30.0f);
	_cloudGroup->ApplyForce(_cloudGroup->GetMass() * gravity);
}
