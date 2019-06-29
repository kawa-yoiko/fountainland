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
}
