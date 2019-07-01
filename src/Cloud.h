#pragma once
#include "Environment.h"

class Cloud :public Environment {
public:
	Cloud();
	~Cloud();

	friend class World;

    void setSize(Vector2 s) { size = s; }
    inline Vector2 getSize() const { return size; }

	void beforeTick() override;
protected:
    Vector2 size;
private:
    void putIntoWorld();
};
