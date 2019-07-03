#include "SceneWin.h"
#include "Global.h"

#include "raylib.h"

SceneWin::SceneWin(double time) : _time(time)
{
}

SceneWin::~SceneWin()
{
}

void SceneWin::update(double dt)
{
    if (IsKeyPressed(KEY_ENTER)) popScene();
}

void SceneWin::draw()
{
    ClearBackground(Color{216, 255, 234});

    drawTextAnchored("Level Complete",
        Vector2 {SCR_W * 0.5, SCR_H * 0.3},
        48, BLACK,
        Vector2{0.5, 0.5}, 12);

    char s[32];
    snprintf(s, sizeof s, "Time: %.2f s", _time);

    drawTextAnchored(s,
        Vector2 {SCR_W * 0.5, SCR_H * 0.45},
        40, Color {64, 64, 64, 255},
        Vector2{0.5, 0.5}, 10);

    drawTextAnchored("Press Enter",
        Vector2{SCR_W * 0.5, SCR_H * 0.7},
        40, GRAY,
        Vector2{0.5, 0.5}, 8);
}
