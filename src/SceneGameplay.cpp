#include "SceneGameplay.h"
#include "Global.h"

extern "C" {
#include "shapes_ext.h"
}

#include "raylib.h"
#include "raymath.h"

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
    if (IsKeyPressed(KEY_TAB)) {
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
    drawTextAnchored("Press Tab to go back",
        Vector2{(float)(SCR_W * 1.5 + kc_getmypos(_kineti)), SCR_H * 0.65},
        40, GRAY,
        Vector2{0.5, 0.5}, 8);

    std::vector<Vector2> p;
    p.push_back(Vector2 {kc_getmypos(_kineti), 0});
    p.push_back(Vector2 {kc_getmypos(_kineti), SCR_H});
    p.push_back(Vector2 {kc_getmypos(_kineti) + SCR_W, SCR_H});
    p.push_back(Vector2 {kc_getmypos(_kineti) + SCR_W / 2, SCR_H * 0.8});
    this->drawGround(p);

    Bubble b(
        Vector2 {(float)(SCR_W * 1.2 + kc_getmypos(_kineti)), SCR_H * 0.6},
        20, 10
    );
    this->drawBubble(&b);

    Cloud c;
    c.setPosition(
        Vector2 {(float)(SCR_W * 1.5 + kc_getmypos(_kineti)), SCR_H * 0.2}
    );
    c.setSize(Vector2 {90, 45});
    this->drawCloud(&c);
    c.setSize(Vector2 {120, 60});
    this->drawCloud(&c);
    c.setAngle(-PI / 6);
    this->drawCloud(&c);

    Fountain f;
    f.setVelocity(10);
    f.setPosition(
        Vector2 {(float)(SCR_W * 0.5 + kc_getmypos(_kineti)), SCR_H * 0.65}
    );
    f.setDirection(PI / 6);
    this->drawFountain(&f);

    Windmill w;
    w.setPosition(
        Vector2 {(float)(SCR_W * 1.75 + kc_getmypos(_kineti)), SCR_H * 0.7}
    );
    w.setFanSize(100);
    w.setAngle(kc_getmypos(_kineti) / 100);
    this->drawWindmill(&w);
}

void SceneGameplay::drawGround(const std::vector<Vector2> &poly)
{
    DrawPolyFilledConcave(poly.data(), poly.size(), Color {216, 255, 192, 192});
}

void SceneGameplay::drawBubble(Bubble *bubble)
{
    Color c = Color {216, 234, 255, 216};
    DrawCircleV(bubble->bubblePos, bubble->bubbleSize, c);
}

void SceneGameplay::drawCloud(Cloud *cloud)
{
    Vector2 p = cloud->getPosition();
    Vector2 s = cloud->getSize();
    DrawRectanglePro(
        Rectangle {p.x, p.y, s.x, s.y},
        Vector2 {s.x / 2, s.y / 2},
        cloud->getAngle() / PI * 180,
        Color {234, 255, 255, 216}
    );
}

void SceneGameplay::drawFountain(Fountain *fountain)
{
    Vector2 p = fountain->getPosition();
    int v = fountain->getVelocity();
    double a = fountain->getDirection();
    DrawLineEx(
        p,
        Vector2 {p.x + v * 15 * cosf(a), p.y + v * 15 * sinf(a)},
        6,
        Color {128, 192, 255, 255}
    );
}

void SceneGameplay::drawWindmill(Windmill *windmill)
{
    Vector2 p = windmill->getPosition();
    float s = windmill->getFanSize();
    DrawLineEx(
        p,
        Vector2 {p.x, SCR_H},
        12,
        Color {216, 192, 128, 255}
    );
    DrawRectanglePro(
        Rectangle {p.x, p.y, s * 2, 10},
        Vector2 {s, 5},
        windmill->getAngle() / PI * 180,
        Color {216, 216, 160, 255}
    );
    DrawRectanglePro(
        Rectangle {p.x, p.y, s * 2, 10},
        Vector2 {s, 5},
        (windmill->getAngle() + PI / 2) / PI * 180,
        Color {216, 216, 160, 255}
    );
}
