#pragma once
#include "Environment.h"

class Cloud :public Environment {
public:
	Cloud();
	~Cloud() {}

    // XXX: Should this be a base class interface?
    void putIntoWorld();

    void setSize(Vector2 s) { size = s; }
    inline Vector2 getSize() const { return size; }

protected:
    Vector2 size;
};
