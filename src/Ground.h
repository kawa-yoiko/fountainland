#pragma once
#include "Environment.h"
#include <vector>

class Ground :public Environment {
public:
	Ground();

	friend class World;

	//Need absolute position here
	//The ground is a broken line that connects all the points in their order
	void setGroundBoundary(std::vector<b2Vec2> pts) { points = pts; }

	std::vector<b2Vec2> points;

private:
	void addToWorld();
};