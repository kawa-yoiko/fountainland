#pragma once
#include "Interactable.h"

class Environment :public Interactable {
public:
	virtual ~Environment() {}

	//Controllable by the player
	void setAngle(double theta);

	//Called only once at the start of each level.
	void setPosition(b2Vec2 pos);

	double getAngle() const;
	b2Vec2 getPosition() const;

	Environment();

private:
	//The angle controlled by the player
	double angle;
	//Position for the stable environment
	b2Vec2 position;
};