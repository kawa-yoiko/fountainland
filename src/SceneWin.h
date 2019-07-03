#ifndef _SCENE_WIN_H_
#define _SCENE_WIN_H_

#include "SceneBase.h"

class SceneWin : public Scene {
public:
    SceneWin(double time);
    ~SceneWin();

    virtual void update(double dt) override;
    virtual void draw() override;

protected:
    double _time;
};

#endif
