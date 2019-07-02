#include "Fountain.h"

Fountain::Fountain() : velocity(1), time(500), direction(0), isEmitting(false), fountainBody(nullptr),
emitTime(250), notEmitTime(250), record(0) {
	double proportion = getAngle() / (2.0f * b2_pi);
	type = Type::Fountain;
	emitTime = proportion * time / 2;
	for (int i = 0; i < emitTime; ++i) {
		cycle.push_back(1);
	}
	for (int i = 0; i < notEmitTime; ++i) {
		cycle.push_back(0);
	}
	for (int i = 0; i < 250 - emitTime; ++i) {
		cycle.push_back(1);
	}
}

Fountain::~Fountain(){
	if (fountainBody)
		m_world->DestroyBody(fountainBody);
}

void Fountain::emitWater() {
	const float32 size = 5.0f;
	const int emitRate = 6;

	const b2ParticleGroupDef def;
	b2ParticleGroup* group = m_particleSystem->CreateParticleGroup(def);
	int32 numberOfParticlesCreated = 0;
	int emitRemainder = emitRate;

	b2ParticleDef pd;
	pd.flags = b2_elasticParticle;
	pd.group = group;
	pd.lifetime = 4 - std::min(velocity, 15) / 5;
	// Keep emitting particles on this frame until we only have a
	// fractional particle left.
	while (emitRemainder > 1) {
		emitRemainder -= 1;
		int ran = std::rand() % 11;//generate a random number from 0 to 10
		float32 emitAngle = (float)ran / 40.0f + direction - 0.125f;//angle - 0.125f ~ angle + 0.125f
//		float32 emitAngle = direction;
		const float32 distance = (float32)rand() / (float32)RAND_MAX;
		b2Vec2 positionOnUnitCircle(cos(emitAngle), sin(emitAngle));

		// Initial position.
		pd.position.Set(
			position.x + positionOnUnitCircle.x * distance * size,
			position.y + positionOnUnitCircle.y * distance * size);
		// Send it flying
		pd.velocity = b2Vec2{ velocity * cosf(emitAngle), velocity * sinf(emitAngle) };
		int index = m_particleSystem->CreateParticle(pd);
	}
}

void Fountain::drawFountain() {
	
	b2BodyDef bd;
	bd.position.Set(position.x, position.y);
	bd.angle = angle;
	fountainBody = m_world->CreateBody(&bd);

	b2PolygonShape shape;
	shape.SetAsBox(1.0f, 0.2f, bd.position - b2Vec2{ 0.2f * (float)sin(angle), - 0.2f * (float)cos(angle) }, angle);
	fountainBody->CreateFixture(&shape, 5.0f);
	shape.SetAsBox(0.3f, 0.2f, bd.position - b2Vec2{ 0.2f * (float)cos(angle), 0.2f * (float)sin(angle) }, 90 - angle);
	fountainBody->CreateFixture(&shape, 5.0f);
	shape.SetAsBox(1.0f, 0.2f, bd.position + b2Vec2{ 0.2f * (float)sin(angle), - 0.2f * (float)cos(angle) }, angle);
	fountainBody->CreateFixture(&shape, 5.0f);
}

void Fountain::beforeTick() {
	isEmitting = cycle[record];
	if (isEmitting) emitWater();
	changeRecord();
}
