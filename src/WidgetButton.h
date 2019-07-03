#ifndef _WIDGET_BUTTON_H_
#define _WIDGET_BUTTON_H_

#include "WidgetBase.h"

#include "raylib.h"

#include <functional>

// Button widget.
// Takes hold of Texture data and unload them at destruction

class Button : public Widget {
public:
    typedef std::function<void (Button *)> callback_t;

    Button(Texture normalTex, Texture activeTex, Vector2 anchor, callback_t cb)
      : _normalTex(normalTex), _activeTex(activeTex), _anchor(anchor),
        _cb(cb), _isActive(false)
    { }
    virtual ~Button() override;

    void changeTexture(Texture normalTex, Texture activeTex);

    virtual bool mouseHold(int x, int y) override;
    virtual bool mouseMove(int x, int y) override;
    virtual void mouseRelease(int x, int y) override;
    virtual void draw() override;

protected:
    Texture _normalTex, _activeTex;
    Vector2 _anchor;
    callback_t _cb;

    bool _isActive;
};

#endif
