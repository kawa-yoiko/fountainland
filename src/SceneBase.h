#ifndef _SCENE_BASE_H_
#define _SCENE_BASE_H_

class Scene {
public:
    Scene() { }
    virtual ~Scene() { }

    virtual void update(double dt) = 0;
    virtual void draw() = 0;
};

#endif
