#pragma once
#include "Interactable.h"

class Trigger :public Interactable {
public:
	virtual ~Trigger() = 0;

	//Called when the trigger is triggered by user events
	virtual void trigger() = 0;


	Trigger();
};