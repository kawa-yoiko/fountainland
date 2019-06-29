#pragma once
#include "raylib.h"
#include "Box2D/Box2D.h"

class GameObject {
public:
	virtual ~GameObject() = 0;
	b2World* getWorld() { return m_world; }

	GameObject();
private:
	b2World* m_world;
};