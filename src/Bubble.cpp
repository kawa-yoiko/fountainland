#include "Bubble.h"

Bubble::Bubble(Vector2 pos, float32 size, float32 impact) : bubblePos(pos), 
bubbleSize(size), bubbleImpact(impact), bubbleBody(nullptr) {
	type = Type::Bubble;
}

void Bubble::putIntoWorld() {
	b2World* world = getWorld();
	b2BodyDef bodyDef;
	bodyDef.position.Set(bubblePos.x, bubblePos.y);
	b2Body* body = world->CreateBody(&bodyDef);
	b2CircleShape bubbleShape;
	bubbleShape.m_p.Set(bubblePos.x, bubblePos.y);
	bubbleShape.m_radius = bubbleSize;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bubbleShape;
	//density & friction defaulted
	//impact to be done
	//color to be done?
	body->CreateFixture(&fixtureDef);
	bubbleBody = body;
	return;
}

void Bubble::trigger() {
	b2ParticleSystem* p = m_world->GetParticleSystemList();
	while (p != NULL) {
		for (int i = 0; i < p->GetParticleCount(); ++i) {
			b2Vec2 tmp = p->GetPositionBuffer()[i];
			const b2Vec2 pos(bubblePos.x, bubblePos.y);//change form Vector2 to const b2Vec2
			float32 distanceSquare = b2DistanceSquared(tmp, pos);
			b2Vec2 delta = (tmp - pos) * bubbleImpact / distanceSquare;
			//delta ~ bubbleImpact * (distance)^-1
			p->GetVelocityBuffer()[i] += delta;
		}
		p = p->GetNext();
	}
	m_world->DestroyBody(bubbleBody);//The bubble has already exploded.
	bubbleBody = nullptr;//May cause error?? I am not sure how to do this.
	return;
}

Bubble::~Bubble(){
	if(bubbleBody)
		m_world->DestroyBody(bubbleBody);
	if (m_particleSystem)
		m_world->DestroyParticleSystem(m_particleSystem);
}
