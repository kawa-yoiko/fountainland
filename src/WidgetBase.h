#ifndef _WIDGET_BASE_H_
#define _WIDGET_BASE_H_

#include "raylib.h"

class Widget {
public:
    Widget() : _enabled(true) { }
    virtual ~Widget() { }

    inline void setPosition(Vector2 pos) { _pos = pos; }
    inline Vector2 getPosition() const { return _pos; }

    inline void setEnabled(bool enabled) { _enabled = enabled; }
    inline bool isEnabled() const { return _enabled; }

    virtual bool mouseHold(int x, int y) = 0;
    virtual bool mouseMove(int x, int y) = 0;
    virtual void mouseRelease(int x, int y) = 0;
    virtual void draw() = 0;

protected:
    Vector2 _pos;
    bool _enabled;
};

#endif
