#ifndef _SCENE_GAMEPLAY_H_
#define _SCENE_GAMEPLAY_H_

#include "SceneBase.h"

class SceneGameplay : public Scene {
public:
    SceneGameplay();
    ~SceneGameplay();

    virtual void update(double dt) override;
    virtual void draw() override;
};

#endif
