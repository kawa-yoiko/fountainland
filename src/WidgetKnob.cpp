#include "WidgetKnob.h"

#include <cmath>

Knob::Knob(double value, callback_t cb)
  : _cb(cb), _isActive(false), _value(value)
{
}

Knob::~Knob()
{
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
        _value = _initialY - (double)y / SPEED;
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
        DrawCircleV(_pos, 24, Color {255, 255, 255, 255});
        for (const auto &p : _sectors)
            DrawCircleSector(_pos, 24,
                90 - p.first, 90 - p.second, 12, Color {128, 128, 255, 255});
        DrawLineV(_pos,
            Vector2 {(float)(_pos.x + 24 * cos(_value)), (float)(_pos.y + 24 * sin(_value))},
            Color {0, 0, 0, 255}
        );
    }
}
