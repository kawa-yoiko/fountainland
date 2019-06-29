#pragma once
#include "GameObject.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Particle/b2ParticleGroup.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"


class Player :public GameObject {
public:
	Player(int x,int y);

	b2ParticleSystem* particleSystem;
	b2ParticleGroup* playerGroup;

	friend b2ParticleSystem;
	friend b2ParticleGroup;

	b2Vec2 getLinearVelocity() const{ return playerGroup->GetLinearVelocity(); }
	void applyLinearImpluse(const b2Vec2& impluse) { playerGroup->ApplyLinearImpulse(impluse); }
	const b2Vec2 &getPosition() const { return playerGroup->GetPosition(); }
private:
	b2CircleShape playerShape;
	b2ParticleGroupDef playerDef;
};