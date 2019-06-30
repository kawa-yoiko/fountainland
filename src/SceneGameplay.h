#ifndef _SCENE_GAMEPLAY_H_
#define _SCENE_GAMEPLAY_H_

#include "SceneBase.h"

extern "C" {
#include "kineticroll/kc_linearscroll.h"
}
#include "raylib.h"

#include <vector>

class SceneGameplay : public Scene {
public:
    SceneGameplay();
    ~SceneGameplay();

    virtual void update(double dt) override;
    virtual void draw() override;

    bool isScrollRefreshingX;

protected:
    kc_linearscroll *_kineti;

    bool _isMouseDown;

    void drawGround(const std::vector<Vector2> &poly);
};

#endif
