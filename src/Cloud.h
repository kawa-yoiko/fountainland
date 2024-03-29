#pragma once
#include "Environment.h"

class Cloud :public Environment {
public:
	Cloud();
	~Cloud();

	friend class World;

    void setSize(Vector2 s) { size = s; }
    inline Vector2 getSize() const { return size; }

    void setAngle(double a) override;

    inline int getParticleCount() const {
        return _particleSys->GetParticleCount();
    }
    inline b2Vec2 *getParticlePositions() const {
        return _particleSys->GetPositionBuffer();
    }

	void beforeTick() override;
protected:
    Vector2 size;
    b2ParticleSystem *_particleSys;
	b2ParticleGroup* _cloudGroup;
private:
    void putIntoWorld();
};
