#pragma once
#include "Environment.h"
#include "Box2D/Dynamics/Joints/b2RopeJoint.h"

class Windmill :public Environment {
public:
	Windmill();
	
	inline void setFanSize(float s) { fanSize = s; }
        inline float getFanSize() const { return fanSize; }

private:
	void addToWorld();
        float fanSize;
	double windSpeed;
};
