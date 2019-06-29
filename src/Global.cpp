#include "SceneBase.h"

#include "raylib.h"
#include <vector>

static std::vector<Scene *> sceneStack;
static double lastTime = -1;
static Font globalFont;

void preload()
{
    globalFont = GetFontDefault();
}

void pushScene(Scene *scene)
{
    sceneStack.push_back(scene);
}

void popScene()
{
    if (!sceneStack.empty()) {
        delete sceneStack.back();
        sceneStack.pop_back();
    }
}

Vector2 drawTextAnchored(
    const char *text, Vector2 pos, int sz, Color c,
    Vector2 anchor, float spacing)
{
    Vector2 textSize = MeasureTextEx(globalFont, text, sz, spacing);
    DrawTextEx(globalFont, text, Vector2{
        pos.x - textSize.x * anchor.x, pos.y - textSize.y * anchor.y
    }, sz, spacing, c);
    return textSize;
}

void draw()
{
    double dt = (lastTime == -1 ? 0 : GetTime() - lastTime);
    lastTime = GetTime();
    if (!sceneStack.empty()) {
        sceneStack.back()->update(dt);
        sceneStack.back()->draw();
    }
}
