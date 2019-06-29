#pragma once
#include "GameObject.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Particle/b2ParticleGroup.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"


class Player :public GameObject {
public:
	Player(int x,int y);

	b2ParticleSystem* particleSystem;

	friend b2ParticleSystem;

private:
	b2CircleShape playerShape;
	b2ParticleGroupDef playerDef;

};