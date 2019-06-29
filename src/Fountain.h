#pragma once
#include "Environment.h"

class Fountain : public Environment {
public:
	Fountain(int v, int t) : velocity(v) , time(t) {}
	Fountain() : velocity(1) , time(0) {}
	~Fountain() {}
	void emitWater();
	void drawFountain();
private:
	int velocity;
	int time; //ms(how often does it emit water)
};