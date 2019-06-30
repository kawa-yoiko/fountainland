#include "Bubble.h"

Bubble::Bubble(Vector2 pos, int size, int impact) : bubblePos(pos), 
bubbleSize(size), bubbleImpact(impact) {
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
	return;
}

void Bubble::trigger() {

}
