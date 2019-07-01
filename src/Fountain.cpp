#include "Fountain.h"

Fountain::Fountain() : velocity(1), time(0), direction(0), isEmitting(false), fountainBody(nullptr) {
	type = Type::Fountain;
}

Fountain::~Fountain(){
	if (fountainBody)
		m_world->DestroyBody(fountainBody);
}

void Fountain::emitWater() {
	int m_count = 0;
	const int e_count = 4;
	while (m_count < e_count)
	{
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		int ran = std::rand() % 11;//generate a random number from 0 to 10
		double emit_angle = (float)ran / 40.0f + angle - 0.125f;//angle - 0.125f ~ angle + 0.125f
		bd.position.Set(position.x + (float)(2 * ran - 10) / 200, position.y + (float)(2 * ran - 10) / 200);
		bd.linearVelocity.Set(velocity * cos(emit_angle), velocity * sin(emit_angle));
		b2Body* body = m_world->CreateBody(&bd);

		b2PolygonShape shape;
		shape.SetAsBox(0.025f, 0.025f);
		body->CreateFixture(&shape, 1.0f);

		++m_count;
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
	
	return;
}

void Fountain::beforeTick() {
	if (isEmitting) emitWater();
}