#include "WidgetKnob.h"

Knob::Knob(callback_t cb)
  : _cb(cb), _isActive(false), _value(0)
{
    _knobTex = LoadTexture("Sprite-0001.png");
}

Knob::~Knob()
{
    UnloadTexture(_knobTex);
}

bool Knob::mouseHold(int x, int y)
{
    float x0 = _pos.x - HALF_SIDE;
    float y0 = _pos.y - HALF_SIDE;
    if (x >= x0 && x < x0 + HALF_SIDE * 2 &&
        y >= y0 && y < y0 + HALF_SIDE * 2)
    {
        _isActive = true;
        _initialY = _value + (double)y / SPEED;
        return true;
    }
    return false;
}

static inline double clamp_double(double val, double min, double max)
{
    return (val > min ? (val < max ? val : max) : min);
}

bool Knob::mouseMove(int x, int y)
{
    if (_isActive) {
        _value = clamp_double(_initialY - (double)y / SPEED, 0, 1);
        _cb(_value);
    }
    return _isActive;
}

void Knob::mouseRelease(int x, int y)
{
    _isActive = false;
}

void Knob::draw()
{
    if (_isActive) {
        DrawTexture(
            _knobTex,
            _pos.x - _knobTex.width / 2,
            _pos.y - _knobTex.height / 2,
            Color {255, 255, 255, 255}
        );
    }
}
