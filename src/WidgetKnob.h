#ifndef _WIDGET_KNOB_H_
#define _WIDGET_KNOB_H_

#include "WidgetBase.h"

#include "raylib.h"

#include <functional>

// Knob widget.
// Takes hold of Texture data and unload them at destruction

class Knob : public Widget {
public:
    typedef std::function<void (double)> callback_t;

    Knob(double value, callback_t cb);
    virtual ~Knob() override;

    virtual bool mouseHold(int x, int y) override;
    virtual bool mouseMove(int x, int y) override;
    virtual void mouseRelease(int x, int y) override;
    virtual void draw() override;

    static const int HALF_SIDE = 40;
    static const int SPEED = 240;

protected:
    callback_t _cb;

    double _initialY;
    bool _isActive;
    double _value;
};

#endif

