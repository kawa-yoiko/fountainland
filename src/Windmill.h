#pragma once
#include "Environment.h"
#include "Box2D/Dynamics/Joints/b2RopeJoint.h"

class Windmill :public Environment {
public:
	Windmill();
	~Windmill();
	
	inline void setFanSize(float s) { fanSize = s; }
    inline float getFanSize() const { return fanSize; }
	double getAngle() const override;
	void setAngle(double theta) override;
	void setVelocity(float32 v) { angularVelocity = v; }

	friend class World;

private:
	float32 angularVelocity;
	void addToWorld();
    float fanSize;
//	double windSpeed;
	b2Body* polygon_body;
	b2Body* ground;
};
