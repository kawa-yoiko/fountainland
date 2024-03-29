#pragma once
#include "Environment.h"
#include <utility>
#include <vector>

class Fountain : public Environment {
public:
	Fountain(std::vector<bool> cycle);
	~Fountain();
	void emitWater();
	void drawFountain();// not used.

	inline void setDirection(float d) { direction = d; }
	inline double getDirection() const { return direction; }
	inline void setVelocity(int v) { velocity = v; }
	inline int getVelocity() const { return velocity; }

    void setAngle(double a) override;
    std::vector<std::pair<double, double>> getEmissionSectors();

	b2Vec2* getParticleLocation() const { return system->GetPositionBuffer(); }
	void beforeTick() override;
	b2ParticleSystem* system;
private:
	int velocity;
	double direction;
	b2Body* fountainBody;

	std::vector<bool> _cycle;
        int _ptr;
};
