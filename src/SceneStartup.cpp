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
}
