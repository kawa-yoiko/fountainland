#include "Cloud.h"

Cloud::Cloud() : _cloudGroup(nullptr) {
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

    b2Vec2 *p = _particleSys->GetPositionBuffer();
    b2Vec2 **u = (b2Vec2 **)_particleSys->GetUserDataBuffer();
    int k = _cloudGroup->GetBufferIndex();
    int n = _cloudGroup->GetParticleCount();
    for (int i = k; i < k + n; i++) u[i] = new b2Vec2(p[i] - pos);
}

void Cloud::setAngle(double a)
{
    Environment::setAngle(a);
    if (_cloudGroup) {
        b2Vec2 *p = _particleSys->GetPositionBuffer();
        b2Vec2 **u = (b2Vec2 **)_particleSys->GetUserDataBuffer();
        int k = _cloudGroup->GetBufferIndex();
        int n = _cloudGroup->GetParticleCount();
        b2Vec2 p0(getPosition().x, getPosition().y);
        double cos_a = cos(a), sin_a = sin(a);
        for (int i = k; i < k + n; i++) {
            p[i].x = p0.x + u[i]->x * cos_a - u[i]->y * sin_a;
            p[i].y = p0.y + u[i]->x * sin_a + u[i]->y * cos_a;
        }
    }
}

//this should be done every step in the world
void Cloud::beforeTick() {
	b2Vec2 gravity(0.0f, -30.0f);
	_cloudGroup->ApplyForce(_cloudGroup->GetMass() * gravity);
    b2Vec2 *v = _particleSys->GetVelocityBuffer();
    int k = _cloudGroup->GetBufferIndex();
    int n = _cloudGroup->GetParticleCount();
    for (int i = k; i < k + n; i++) v[i] = b2Vec2_zero;
}
