#include "SceneGameplay.h"
#include "Global.h"

#include "raylib.h"

SceneGameplay::SceneGameplay()
{
}

SceneGameplay::~SceneGameplay()
{
}

void SceneGameplay::update(double dt)
{
    if (IsKeyPressed(KEY_GRAVE)) {
        popScene();
        return;
    }
}

void SceneGameplay::draw()
{
    ClearBackground((Color){216, 216, 255});

    drawTextAnchored("Press Grave (`) to go back",
        (Vector2){SCR_W * 0.5, SCR_H * 0.65},
        40, GRAY,
        (Vector2){0.5, 0.5}, 8);
}
