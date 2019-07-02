#include "WidgetButton.h"

Button::~Button()
{
    UnloadTexture(_normalTex);
    UnloadTexture(_activeTex);
}

bool Button::mouseHold(int x, int y)
{
    float x0 = _pos.x - _anchor.x * _normalTex.width;
    float y0 = _pos.y - _anchor.y * _normalTex.height;
    if (x >= x0 && x < x0 + _normalTex.width &&
        y >= y0 && y < y0 + _normalTex.height)
    {
        _isActive = true;
        return true;
    }
    return false;
}

bool Button::mouseMove(int x, int y)
{
    return _isActive;
}

void Button::mouseRelease(int x, int y)
{
    if (_isActive) {
        float x0 = _pos.x - _anchor.x * _normalTex.width;
        float y0 = _pos.y - _anchor.y * _normalTex.height;
        if (x >= x0 && x < x0 + _normalTex.width &&
            y >= y0 && y < y0 + _normalTex.height)
        {
            _cb(this);
        }
    }
    _isActive = false;
}

void Button::draw()
{
    float x0 = _pos.x - _anchor.x * _normalTex.width;
    float y0 = _pos.y - _anchor.y * _normalTex.height;
    DrawTexture(
        _isActive ? _activeTex : _normalTex,
        x0, y0,
        Color {255, 255, 255, 255}
    );
}
