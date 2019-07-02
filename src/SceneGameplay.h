#ifndef _SCENE_GAMEPLAY_H_
#define _SCENE_GAMEPLAY_H_

#include "SceneBase.h"
#include "Bubble.h"
#include "Cloud.h"
#include "Fountain.h"
#include "Ground.h"
#include "Windmill.h"
#include "World.h"

extern "C" {
#include "kineticroll/kc_linearscroll.h"
}
#include "raylib.h"

#include <vector>

class Widget;

class SceneGameplay : public Scene {
public:
    SceneGameplay();
    ~SceneGameplay();

    virtual void update(double dt) override;
    virtual void draw() override;

    void setScrollPosition(float x);

    bool isScrollRefreshingX;

    Vector2 _cam;   // XXX

    std::vector<Widget *> _stageWidgets;
    std::vector<Widget *> _stageKnobs;

    constexpr static const float SCALE = 10;

protected:
    kc_linearscroll *_kineti;

    bool _isMouseDown;

    World *_world;

    void drawGround(Ground *ground);
    void drawBubble(Bubble *bubble);
    void drawCloud(Cloud *cloud);
    void drawFountain(Fountain *fountain);
    void drawWindmill(Windmill *windmill);
    void drawPlayer(Player *player);

    inline Vector2 posInCam(Vector2 p) {
        return Vector2 {p.x * SCALE + _cam.x, p.y * SCALE + _cam.y};
    }

    enum {
        PREPARING,
        RUNNING,
        RESTARTING
    } _state;

    void changeState();
};

#endif
