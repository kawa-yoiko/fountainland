#pragma once
#include "Trigger.h"

class Bubble :public Trigger {
public:
	Bubble(Vector2& pos, int size, int impact);
	void putIntoWorld();
	~Bubble() {}
private:
	Vector2 bubblePos;
	int bubbleSize;
	int bubbleImpact;//color has something to do with its impact
};