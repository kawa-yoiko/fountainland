#pragma once
#include "Environment.h"

class Fountain : public Environment {
public:
	Fountain();
	~Fountain();
	void emitWater();
	void drawFountain();// not used.

	inline void setDirection(float d) { direction = d; }
	inline double getDirection() const { return direction; }
	inline void setVelocity(int v) { velocity = v; }
	inline int getVelocity() const { return velocity; }
	
	void beforeTick() override;
private:
	int velocity;
	int time; //ms(how often does it emit water)
	double direction;
	bool isEmitting;
	b2Body* fountainBody;
};
