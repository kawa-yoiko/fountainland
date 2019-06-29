#pragma once
#include "GameObject.h"

class Interactable:public GameObject {
public:
	enum Type {
		Bubble,
		Cloud,
		Fountain,
		Windmill,
		TypeCount
	};

	Interactable();
	virtual ~Interactable() = 0;
	Type getType() const;

	Type type;

	//Tell whether the interactable can still be interacted during gameplay.
	bool isTrigger;
};


inline Interactable::Type Interactable::getType() const {
	return type;
}