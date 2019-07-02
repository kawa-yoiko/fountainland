#pragma once
#include "Environment.h"
#include <vector>

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

	inline void setEmitTime(int i) { emitTime = i; }
	inline void setNotEmitTime(int i) { notEmitTime = i; }

	b2Vec2* getParticleLocation() const { return system->GetPositionBuffer(); }
	void beforeTick() override;
	inline void changeRecord() {
		record = (record + 1) % cycle.size();
	}
	b2ParticleSystem* system;
private:
	int velocity;
	int time; //ms(how often does it emit water)
	double direction;
	bool isEmitting;
	b2Body* fountainBody;

	int record;
	int emitTime;
	int notEmitTime;
	std::vector<bool> cycle;
};
