#include "Ground.h"

Ground::Ground() {
	type = Type::Ground;
}

void Ground::addToWorld(){
	b2Body* grnd = nullptr;
	b2BodyDef bd;
	grnd = m_world->CreateBody(&bd);
	b2EdgeShape shape;
	b2FixtureDef fd;
	fd.shape = &shape;
	for (int i = 1;i < points.size();++i) {
		shape.Set(points[i - 1], points[i]);
		grnd->CreateFixture(&fd);
	}
}
