#include "Windmill.h"

Windmill::Windmill() :fanSize(0.0f), polygon_body(nullptr), ground(nullptr) {
	type = Type::Windmill;
}

Windmill::~Windmill() {
	if (ground)
		m_world->DestroyBody(ground);
	if (polygon_body)
		m_world->DestroyBody(polygon_body);
}

double Windmill::getAngle() const {
	return (double)polygon_body->GetAngle() + angle;
}

void Windmill::setAngle(double theta) {
	angle = theta;
	if (polygon_body)
		polygon_body->SetTransform(polygon_body->GetPosition(), polygon_body->GetAngle() + theta);
}

void Windmill::addToWorld() {
	b2BodyDef bd;
	ground = m_world->CreateBody(&bd);
	b2PolygonShape polygon_shape[2];
	b2BodyDef polygon_bd;
	polygon_bd.position.Set(position.x, position.y - 1.5 * fanSize);
	polygon_bd.type = b2_dynamicBody;
	polygon_bd.bullet = true;
	polygon_body = m_world->CreateBody(&polygon_bd);

	polygon_shape[0].SetAsBox(fanSize, 0.5f, b2Vec2(0.0f, 1.5 * fanSize), angle);
	polygon_shape[1].SetAsBox(fanSize, 0.5f, b2Vec2(0.0f, 1.5 * fanSize), angle + 0.5 * b2_pi);

	polygon_body->CreateFixture(&polygon_shape[0], 2.0f);
	polygon_body->CreateFixture(&polygon_shape[1], 2.0f);

	float32 w = 0.0f;
	polygon_body->SetAngularVelocity(w);
	polygon_body->SetLinearVelocity(b2Vec2(-8.0f * w, 0.0f));
	b2RevoluteJointDef rjd;
	rjd.Initialize(ground, polygon_body, b2Vec2(position.x, position.y));
	rjd.enableLimit = false;
	m_world->CreateJoint(&rjd);
}
