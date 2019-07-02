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
#include <iostream>

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

void SceneGameplay::setScrollPosition(float x)
{
    kc_setmypos(_kineti, x);
}

SceneGameplay::SceneGameplay()
{
    _kineti = kc_init();
    kc_setuserdata(_kineti, this);
    kc_setcallback_0(_kineti, START_REFRESHING, startRefreshing);
    kc_setcallback_0(_kineti, STOP_REFRESHING, stopRefreshing);
    kc_setcallback_1(_kineti, UPDATE_POSITION, updatePos);
    kc_setvisiblesize(_kineti, SCR_W);
    kc_setmypos(_kineti, 0);

    _isMouseDown = false;
    isScrollRefreshingX = false;

    // XXX...
    _world = loadLevel("level.txt");
    if (!_world) _world = loadLevel("../level.txt");
    Player *player = new Player();
    player->setPosition(Vector2 {14, 0});
    _world->addPlayer(player);

    kc_setcontentsize(_kineti, _world->getWidth() * SCALE);

    _cam = Vector2 {0, 0};
    _state = PREPARING;

    Button *button = new Button(
        LoadTexture("Sprite-0001.png"),
        LoadTexture("Sprite-0002.png"),
        Vector2 {1, 0},
        [this] (Button *target) {
            this->changeState();
            return;
        }
    );
    button->setPosition(Vector2 {SCR_W - 6, 6});
    this->addWidget(button);

    for (Interactable *obj : _world->interactableList) {
        if (!obj->isTrigger) {  // XXX: Add isKnobSetup?
            Knob *knob = new Knob(
                ((Environment *)obj)->getAngle(),
                [obj] (double val) { ((Environment *)obj)->setAngle(val); }
            );
            Vector2 p = ((Environment *)obj)->getPosition();
            knob->setPosition(Vector2 {p.x * SCALE, p.y * SCALE});
            if (obj->type == Interactable::Fountain) {
                knob->setSectors(((Fountain *)obj)->getEmissionSectors());
            }
            this->addWidget(knob);
            _stageWidgets.push_back(knob);
            _stageKnobs.push_back(knob);
        } else {    // XXX: Add support for things other than bubbles
            Button *button = new Button(
                LoadTexture("Sprite-0003.png"),
                LoadTexture("Sprite-0004.png"),
                Vector2 {0.5, 0.5},
                [this, obj] (Button *target) {
                    if (_state != PREPARING) {
                        ((Trigger *)obj)->trigger();
                        target->setEnabled(false);
                    }
                }
            );
            Vector2 p = ((Bubble *)obj)->getBubblePosition();
            button->setPosition(Vector2 {p.x * SCALE, p.y * SCALE});
            this->addWidget(button);
            _stageWidgets.push_back(button);
        }
    }
}

void SceneGameplay::changeState()
{
    if (_state == PREPARING) {
        _state = RUNNING;
        for (Widget *w : _stageKnobs) w->setEnabled(false);
    } else if (_state == RUNNING) {
        _state = RESTARTING;
        SceneGameplay *scene = new SceneGameplay();
        scene->setScrollPosition(kc_getmypos(_kineti));
        replaceScene(scene);
    }
}

SceneGameplay::~SceneGameplay()
{
    // XXX: Maybe add a method kc_cleanup()
    free(_kineti);
}

void SceneGameplay::update(double dt)
{
    if (IsKeyReleased(KEY_TAB)) {
        popScene();
        return;
    } else if (IsKeyPressed(KEY_ENTER)) {
        changeState();
        return;
    }

    if (::isMouseButtonPressed) {
        kc_activate(_kineti, TOUCH_BEGAN, getMouseX());
    } else if (::isMouseButtonDown) {
        kc_activate(_kineti, TOUCH_MOVED, getMouseX());
    }
    if (::isMouseButtonReleased) {
        kc_activate(_kineti, TOUCH_ENDED, getMouseX());
    }
    if (isScrollRefreshingX) {
        kc_activate(_kineti, REFRESH_TICK, dt);
    }

    if (_state >= RUNNING)
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
}

void SceneGameplay::drawCloud(Cloud *cloud)
{
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
    for (int i = 0; i < n; i += 1)
        DrawCircleV(posInCam(Vector2 {p[i].x, p[i].y}), 3, Color{ 255, 192, 180, 255 });
    rlglDraw();
}
