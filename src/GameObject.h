#pragma once

class GameObject {
public:
	virtual ~GameObject() = 0;
	GameObject();

	//Tell whether the game object is player or not
	bool isPlayer;
};