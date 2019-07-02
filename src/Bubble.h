#pragma once
#include "Trigger.h"

class Bubble :public Trigger {
public:
	Bubble(Vector2 pos, float32 size, float32 impact);

	friend class World;

	void trigger() override;
	void beforeTick() override;
	~Bubble();

	inline Vector2 getBubblePosition() { return bubblePos; }
	inline void setBubblePosition(Vector2 v) { bubblePos = v; }
	inline float32 getBubbleSize() { return bubbleSize; }
	inline void setBubbleSize(float32 r) { bubbleSize = r; }
	inline float32 getBubbleImpact() { return bubbleImpact; }
	inline void setBubbleImpact(float32 imp) { bubbleImpact = imp; }
	inline bool getFlag() { return flag; }
	inline void setFlag(bool b) { flag = b; }
private:
	Vector2 bubblePos;
	float32 bubbleSize;
	float32 bubbleImpact;//color has something to do with its impact
	bool flag;
	void putIntoWorld();//put bubble into the world
	b2Body* bubbleBody;
};
