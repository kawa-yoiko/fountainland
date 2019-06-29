#pragma once
#include "Interactable.h"

class Environment :public Interactable {
public:
	virtual ~Environment() = 0;

	//Called only once at the start of each level.
	virtual void setup() = 0;

	Environment();
};