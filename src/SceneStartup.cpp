#include "SceneStartup.h"
#include "Global.h"
#include "SceneGameplay.h"

#include "raylib.h"

SceneStartup::SceneStartup()
{
}

SceneStartup::~SceneStartup()
{
}

void SceneStartup::update(double dt)
{
    if (IsKeyPressed(KEY_ENTER)) {
        pushScene(new SceneGameplay());
        return;
    }
}

void SceneStartup::draw()
{
    ClearBackground((Color){216, 234, 255});

    drawTextAnchored("Fountainland",
        (Vector2){SCR_W * 0.5, SCR_H * 0.35},
        48, BLACK,
        (Vector2){0.5, 0.5}, 12);

    drawTextAnchored("Press Enter",
        (Vector2){SCR_W * 0.5, SCR_H * 0.65},
        40, GRAY,
        (Vector2){0.5, 0.5}, 8);
}
