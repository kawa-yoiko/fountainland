#pragma once
#include "Trigger.h"

class Bubble :public Trigger {
public:
	Bubble(Vector2 pos, float32 size, float32 impact);

	friend class World;

	void trigger() override;
	~Bubble();
public: // TODO: Use get/set
	Vector2 bubblePos;
	float32 bubbleSize;
	float32 bubbleImpact;//color has something to do with its impact
private:
	void putIntoWorld();//put bubble into the world
	b2Body* bubbleBody;
};
