#pragma once
#include "GameObject.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Particle/b2ParticleGroup.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"


class Player :public GameObject {
public:
	Player(int x, int y);

	b2ParticleGroup* playerGroup;

	friend b2ParticleSystem;
	friend b2ParticleGroup;

	Vector2 getLinearVelocity() const;
	void applyLinearImpluse(const b2Vec2& impluse);
	const Vector2 getPosition() const;
private:
	b2CircleShape playerShape;
	b2ParticleGroupDef playerDef;
};
