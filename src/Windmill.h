#pragma once
#include "Environment.h"
#include "Box2D/Dynamics/Joints/b2RopeJoint.h"

class Windmill :public Environment {
	Windmill(float x, float y);
	
	

private:
	void addToWorld();
	double windSpeed;
};