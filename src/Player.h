#pragma once
#include "GameObject.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Particle/b2ParticleGroup.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"


class Player :public GameObject {
public:
	Player(float x = 0.0, float y = 0.0);
	~Player();

	b2ParticleGroup* playerGroup;

	friend class b2ParticleSystem;
	friend class b2ParticleGroup;
	friend class World;

	int getParticleCount() const;
	inline b2Vec2* getLinearVelocity() const;
	void applyLinearImpluse(const b2Vec2& impluse);
	inline const b2Vec2* getPosition() const;
	inline void setPosition(Vector2 pos) { playerInitPos = pos; }
	
private:
	void addToWorld();
	Vector2 playerInitPos;
	b2CircleShape playerShape;
	b2ParticleGroupDef playerDef;
};
