#include "SceneBase.h"
#include "WidgetBase.h"

void Scene::addWidget(Widget *widget)
{
    _widgets.push_back(widget);
}

bool Scene::widgetsMouseHold(int x, int y)
{
    for (int i = 0; i < _widgets.size(); i++)
        if (_widgets[i]->mouseHold(x, y))
            return true;
    return false;
}

bool Scene::widgetsMouseMove(int x, int y)
{
    for (int i = 0; i < _widgets.size(); i++)
        if (_widgets[i]->mouseMove(x, y))
            return true;
    return false;
}

void Scene::widgetsMouseRelease(int x, int y)
{
    for (int i = 0; i < _widgets.size(); i++)
        _widgets[i]->mouseRelease(x, y);
}

void Scene::widgetsDraw()
{
    for (int i = 0; i < _widgets.size(); i++)
        _widgets[i]->draw();
}
