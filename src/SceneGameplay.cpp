#include "SceneGameplay.h"
#include "Global.h"
#include "LevelLoader.h"
#include "WidgetButton.h"
#include "WidgetKnob.h"

extern "C" {
#include "shapes_ext.h"
}

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include <cstdio>
#include <cstdlib>

static void updatePos(void *__this, float p)
{
    SceneGameplay *_this = (SceneGameplay *)__this;
    float lastX = _this->_cam.x;
    _this->_cam.x = p;
    for (Widget *w : _this->_stageWidgets) {
        Vector2 pos = w->getPosition();
        w->setPosition(Vector2 {pos.x + (p - lastX), pos.y});
    }
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

    // XXX...
    _world = loadLevel("level.txt");
    if (!_world) _world = loadLevel("../level.txt");
    Player *player = new Player();
    player->setPosition(Vector2 {14, 0});
    _world->addPlayer(player);

    _cam = Vector2 {0, 0};

    Button *button = new Button(
        LoadTexture("Sprite-0001.png"),
        LoadTexture("Sprite-0002.png"),
        Vector2 {1, 0},
        [] () { puts("Hi"); }
    );
    button->setPosition(Vector2 {SCR_W - 6, 6});
    this->addWidget(button);

    for (Interactable *obj : _world->interactableList) {
        if (!obj->isTrigger) {  // XXX: Add isKnobSetup?
            Knob *knob = new Knob([obj] (double val) {
                ((Environment *)obj)->setAngle(val);
            });
            Vector2 p = ((Environment *)obj)->getPosition();
            knob->setPosition(Vector2 {p.x * SCALE, p.y * SCALE});
            this->addWidget(knob);
            _stageWidgets.push_back(knob);
        } else {    // XXX: Add support for things other than bubbles
            Button *button = new Button(
                LoadTexture("Sprite-0003.png"),
                LoadTexture("Sprite-0004.png"),
                Vector2 {0.5, 0.5},
                [obj] () {
                    ((Trigger *)obj)->trigger();
                }
            );
            Vector2 p = ((Bubble *)obj)->bubblePos;
            button->setPosition(Vector2 {p.x * SCALE, p.y * SCALE});
            this->addWidget(button);
            _stageWidgets.push_back(button);
        }
    }
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

    if (::isMouseButtonPressed) {
        kc_activate(_kineti, TOUCH_BEGAN, GetMouseX() * 2);
    } else if (::isMouseButtonDown) {
        kc_activate(_kineti, TOUCH_MOVED, GetMouseX() * 2);
    }
    if (::isMouseButtonReleased) {
        kc_activate(_kineti, TOUCH_ENDED, GetMouseX() * 2);
    }
    if (isScrollRefreshingX) {
        kc_activate(_kineti, REFRESH_TICK, dt);
    }

    for (int i = 0; i < 2; i++) _world->tick();
}

void SceneGameplay::draw()
{
    ClearBackground(Color{234, 244, 255});

    drawTextAnchored("Drag me (^-^*)",
        posInCam(Vector2 {SCR_W * 0.5, SCR_H * 0.65}),
        40, GRAY,
        Vector2{0.5, 0.5}, 8);
    drawTextAnchored("Press Tab to go back",
        posInCam(Vector2 {SCR_W * 1.5, SCR_H * 0.65}),
        40, GRAY,
        Vector2 {0.5, 0.5}, 8);

    for (Interactable *obj : _world->interactableList) {
        switch (obj->type) {
        case Interactable::Bubble:
            this->drawBubble((Bubble *)obj);
            break;
        case Interactable::Cloud:
            this->drawCloud((Cloud *)obj);
            break;
        case Interactable::Fountain:
            this->drawFountain((Fountain *)obj);
            //((Fountain *)obj)->emitWater();
            break;
        case Interactable::Ground:
            this->drawGround((Ground *)obj);
            break;
        case Interactable::Windmill:
            this->drawWindmill((Windmill *)obj);
            break;
        default: puts("OvO");
        }
    }

    this->drawPlayer(_world->getPlayer());
}

void SceneGameplay::drawGround(Ground *ground)
{
    std::vector<Vector2> poly;
    for (const b2Vec2 &p : ground->getGroundBoundary()) {
        poly.push_back(posInCam(Vector2 {p.x, p.y}));
    }
    DrawPolyFilledConcave(poly.data(), poly.size(), Color {216, 234, 192, 192});
    rlglDraw();
}

void SceneGameplay::drawBubble(Bubble *bubble)
{
    //Color c = Color {200, 216, 255, 216};
    //DrawCircleV(posInCam(bubble->bubblePos), bubble->bubbleSize, c);
}

void SceneGameplay::drawCloud(Cloud *cloud)
{
    /*Vector2 p = posInCam(cloud->getPosition());
    Vector2 s = cloud->getSize();
    DrawRectanglePro(
        Rectangle {p.x, p.y, s.x * SCALE, s.y * SCALE},
        Vector2 {s.x / 2 * SCALE, s.y / 2 * SCALE},
        cloud->getAngle() / PI * 180,
        Color {244, 255, 255, 216}
    );*/
    const b2Vec2 *p = cloud->getParticlePositions();
    int n = cloud->getParticleCount();
    for (int i = 0; i < n; i += 5)
        DrawCircleV(posInCam(Vector2 {p[i].x, p[i].y}), 3, Color {244, 255, 255, 216});
    rlglDraw();
}

void SceneGameplay::drawFountain(Fountain *fountain)
{
    Vector2 p = posInCam(fountain->getPosition());
    int v = fountain->getVelocity();
    double a = fountain->getDirection();
    DrawLineEx(
        p,
        Vector2 {p.x + v * 50 * cosf(a), p.y + v * 50 * sinf(a)},
        6,
        Color {128, 192, 255, 255}
    );
    rlglDraw();
}

void SceneGameplay::drawWindmill(Windmill *windmill)
{
    Vector2 p = posInCam(windmill->getPosition());
    float s = windmill->getFanSize() * SCALE;
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
    rlglDraw();
}

void SceneGameplay::drawPlayer(Player *player)
{
    const b2Vec2 *p = player->getPosition();
    int n = player->getParticleCount();
    for (int i = 0; i < n; i += 5)
        DrawCircleV(posInCam(Vector2 {p[i].x, p[i].y}), 3, Color{ 255, 192, 180, 255 });
}
