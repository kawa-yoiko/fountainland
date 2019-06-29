#include "SceneGameplay.h"
#include "Global.h"

#include "raylib.h"

#include <cstdio>
#include <cstdlib>

static void updatePos(void *__this, float p)
{
    SceneGameplay *_this = (SceneGameplay *)__this;
}

static void startRefreshing(void *__this)
{
    SceneGameplay *_this = (SceneGameplay *)__this;
    _this->isScrollRefreshingX = true;
}

static void stopRefreshing(void *__this)
{
    SceneGameplay *_this = (SceneGameplay *)__this;
    _this->isScrollRefreshingX = false;
}

SceneGameplay::SceneGameplay()
{
    _kineti = kc_init();
    kc_setuserdata(_kineti, this);
    kc_setcallback_0(_kineti, START_REFRESHING, startRefreshing);
    kc_setcallback_0(_kineti, STOP_REFRESHING, stopRefreshing);
    kc_setcallback_1(_kineti, UPDATE_POSITION, updatePos);
    kc_setvisiblesize(_kineti, SCR_W);
    kc_setcontentsize(_kineti, SCR_W * 2);
    kc_setmypos(_kineti, 0);

    _isMouseDown = false;
    isScrollRefreshingX = false;
}

SceneGameplay::~SceneGameplay()
{
    // XXX: Maybe add a method kc_cleanup()
    free(_kineti);
}

void SceneGameplay::update(double dt)
{
    if (IsKeyPressed(KEY_GRAVE)) {
        popScene();
        return;
    }

    if (IsMouseButtonPressed(0)) {
        kc_activate(_kineti, TOUCH_BEGAN, GetMouseX() * 2);
    } else if (IsMouseButtonDown(0)) {
        kc_activate(_kineti, TOUCH_MOVED, GetMouseX() * 2);
    }
    if (IsMouseButtonReleased(0)) {
        kc_activate(_kineti, TOUCH_ENDED, GetMouseX() * 2);
    }
    if (isScrollRefreshingX) {
        kc_activate(_kineti, REFRESH_TICK, dt);
    }
}

void SceneGameplay::draw()
{
    ClearBackground(Color{216, 216, 255});

    drawTextAnchored("Drag me (^-^*)",
        Vector2{(float)(SCR_W * 0.5 + kc_getmypos(_kineti)), SCR_H * 0.65},
        40, GRAY,
        Vector2{0.5, 0.5}, 8);
    drawTextAnchored("Press Grave (`) to go back",
        Vector2{(float)(SCR_W * 1.5 + kc_getmypos(_kineti)), SCR_H * 0.65},
        40, GRAY,
        Vector2{0.5, 0.5}, 8);
}
