#ifndef _SCENE_BASE_H_
#define _SCENE_BASE_H_

#include <vector>

class Widget;

class Scene {
public:
    Scene() { }
    virtual ~Scene() { }

    virtual void update(double dt) = 0;
    virtual void draw() = 0;

    void addWidget(Widget *widget);
    bool widgetsMouseHold(int x, int y);
    bool widgetsMouseMove(int x, int y);
    void widgetsMouseRelease(int x, int y);
    void widgetsDraw();

protected:
    std::vector<Widget *> _widgets;
};

#endif
