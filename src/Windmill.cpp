#include "Windmill.h"

Windmill::Windmill()
{
	type = Type::Windmill;
}

void Windmill::addToWorld(){
	b2Body* ground = nullptr;
	b2BodyDef bd;
	ground = m_world->CreateBody(&bd);
	b2PolygonShape polygon_shape[2];
	b2Body* polygon_body;
	b2BodyDef polygon_bd;
	polygon_bd.position.Set(position.x, position.y);
	polygon_bd.type = b2_dynamicBody;
	polygon_bd.bullet = true;
	polygon_body = m_world->CreateBody(&polygon_bd);
	polygon_shape[0].SetAsBox(5.0f, 0.5f, b2Vec2(0.0f, 1.5*5.0f), 0 * 0.5 * b2_pi);
	polygon_shape[1].SetAsBox(5.0f, 0.5f, b2Vec2(0.0f, 1.5*5.0f), 1 * 0.5 * b2_pi);

	polygon_body->CreateFixture(&polygon_shape[0], 2.0f);
	polygon_body->CreateFixture(&polygon_shape[1], 2.0f);
	float32 w = 10.0f;
	polygon_body->SetAngularVelocity(w);
	polygon_body->SetLinearVelocity(b2Vec2(-8.0f * w, 0.0f));
	b2RevoluteJointDef rjd;
	rjd.Initialize(ground, polygon_body, b2Vec2(position.x, position.y));
	rjd.enableLimit = false;
	rjd.motorSpeed = 1.0f * b2_pi;
	rjd.maxMotorTorque = 0.0f;
	rjd.enableMotor = true;
	m_world->CreateJoint(&rjd);
}
