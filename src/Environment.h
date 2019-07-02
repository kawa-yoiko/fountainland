#pragma once
#include "Interactable.h"

class Environment :public Interactable {
public:
	virtual ~Environment() {}

	//Controllable by the player
	void setAngle(double theta) { angle = theta; }

	//Called only once at the start of each level.
	void setPosition(Vector2 pos) { position = pos; }

	virtual double getAngle() const { return angle; }
	virtual Vector2 getPosition() const { return position; }

	Environment();

	//The angle controlled by the player
	double angle;

	//Position for the stable environment
	Vector2 position;
};