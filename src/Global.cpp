#include "SceneBase.h"

#include "raylib.h"

#include <map>
#include <vector>

static std::vector<Scene *> sceneStack;
static double lastTime = -1;
static std::map<int, Font> globalFont;

void preload()
{
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

#define DEFAULT_TTF_NUMCHARS    95      // ASCII 32..126 is 95 glyphs

Vector2 drawTextAnchored(
    const char *text, Vector2 pos, int sz, Color c,
    Vector2 anchor, float spacing)
{
    std::map<int, Font>::iterator it = globalFont.find(sz);
    if (it == globalFont.end()) {
        it = globalFont.insert(std::make_pair(
            sz, LoadFontEx("Itim-Regular.otf", sz * 2, NULL, DEFAULT_TTF_NUMCHARS)
        )).first;
    }
    Font &font = it->second;
    Vector2 textSize = MeasureTextEx(font, text, sz, spacing);
    DrawTextEx(font, text, Vector2{
        pos.x - textSize.x * anchor.x, pos.y - textSize.y * anchor.y
    }, sz, spacing, c);
    return textSize;
}

bool isMouseButtonPressed = false;
bool isMouseButtonDown = false;
bool isMouseButtonReleased = false;

void draw()
{
    double dt = (lastTime == -1 ? 0 : GetTime() - lastTime);
    lastTime = GetTime();
    isMouseButtonPressed = false;
    isMouseButtonReleased = false;
    if (!sceneStack.empty()) {
        Scene *s = sceneStack.back();
        if (IsMouseButtonPressed(0)) {
            if (!s->widgetsMouseHold(GetMouseX() * 2, GetMouseY() * 2)) {
                isMouseButtonPressed = true;
                isMouseButtonDown = true;
            }
        } else if (IsMouseButtonDown(0)) {
            s->widgetsMouseMove(GetMouseX() * 2, GetMouseY() * 2);
        }
        if (IsMouseButtonReleased(0)) {
            isMouseButtonReleased = isMouseButtonDown;
            isMouseButtonDown = false;
            s->widgetsMouseRelease(GetMouseX() * 2, GetMouseY() * 2);
        }
        s->update(dt);
        s->draw();
        s->widgetsDraw();
    }
    //printf("%d %d %d\n", (int)isMouseButtonPressed, (int)isMouseButtonDown, (int)isMouseButtonReleased);
}
