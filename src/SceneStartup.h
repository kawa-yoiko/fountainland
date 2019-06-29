#ifndef _SCENE_STARTUP_H_
#define _SCENE_STARTUP_H_

#include "SceneBase.h"

class SceneStartup : public Scene {
public:
    SceneStartup();
    ~SceneStartup();

    virtual void update(double dt) override;
    virtual void draw() override;
};

#endif
