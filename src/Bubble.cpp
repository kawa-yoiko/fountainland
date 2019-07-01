#include "Bubble.h"

Bubble::Bubble(Vector2 pos, float32 size, float32 impact) : bubblePos(pos), 
bubbleSize(size), bubbleImpact(impact), bubbleBody(nullptr) {
	type = Type::Bubble;
}

void Bubble::putIntoWorld() {
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
	return;
}

Bubble::~Bubble(){
	if (m_particleSystem)
		m_world->DestroyParticleSystem(m_particleSystem);
}
