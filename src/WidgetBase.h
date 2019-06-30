#ifndef _WIDGET_BASE_H_
#define _WIDGET_BASE_H_

#include "raylib.h"

class Widget {
public:
    Widget() { }
    virtual ~Widget() { }

    inline void setPosition(Vector2 pos) { _pos = pos; }
    inline Vector2 getPosition() const { return _pos; }

    virtual bool mouseHold(int x, int y) = 0;
    virtual bool mouseMove(int x, int y) = 0;
    virtual void mouseRelease(int x, int y) = 0;
    virtual void draw() = 0;

protected:
    Vector2 _pos;
};

#endif
