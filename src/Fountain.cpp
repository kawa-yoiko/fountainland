#include "Fountain.h"

void Fountain::emitWater() {
	int m_count = 0;
	const int e_count = 1000;
	if (m_count < e_count)
	{
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(position.x, position.y);
		double emit_angle = rand() % 4 + angle - 2;
		bd.linearVelocity.Set(velocity * cos(emit_angle), velocity * sin(emit_angle));
		b2Body* body = m_world->CreateBody(&bd);

		b2PolygonShape shape;
		shape.SetAsBox(0.25f, 0.25f);
		body->CreateFixture(&shape, 1.0f);

		++m_count;
	}
}

void Fountain::drawFountain() {
	
	b2BodyDef bd;
	bd.position.Set(position.x, position.y);
	bd.angle = angle;
	b2Body* body = m_world->CreateBody(&bd);

	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 0.2f, bd.position - b2Vec2{ 0.2f * (float)sin(angle), - 0.2f * (float)cos(angle) }, angle);
	body->CreateFixture(&shape, 5.0f);
	shape.SetAsBox(0.3f, 0.2f, bd.position - b2Vec2{ 0.2f * (float)cos(angle), 0.2f * (float)sin(angle) }, 90 - angle);
	body->CreateFixture(&shape, 5.0f);
	shape.SetAsBox(0.5f, 0.2f, bd.position + b2Vec2{ 0.2f * (float)sin(angle), - 0.2f * (float)cos(angle) }, angle);
	body->CreateFixture(&shape, 5.0f);
	
	return;
}
