#include "SceneBase.h"

#include "raylib.h"
#include <vector>

static std::vector<Scene *> sceneStack;
static double lastTime = -1;

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

void draw()
{
    double dt = (lastTime == -1 ? 0 : GetTime() - lastTime);
    lastTime = GetTime();
    if (!sceneStack.empty()) {
        sceneStack.back()->update(dt);
        sceneStack.back()->draw();
    }
}
