#pragma once
#include "Trigger.h"

class Bubble :public Trigger {
public:
	Bubble(Vector2 pos, int size, int impact);
	void putIntoWorld();//put bubble into the world
	void trigger() override;
	~Bubble() {}
public: // TODO: Use get/set
	Vector2 bubblePos;
	int bubbleSize;
	int bubbleImpact;//color has something to do with its impact
};
