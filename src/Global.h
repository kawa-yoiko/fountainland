#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "SceneBase.h"

#include "raylib.h"

#define SCR_W   800
#define SCR_H   480

void preload();

void pushScene(Scene *);
void replaceScene(Scene *);
void popScene();

Vector2 drawTextAnchored(
    const char *text, Vector2 pos, int sz, Color c,
    Vector2 anchor = Vector2{0.5, 0.5}, float spacing = 0);

extern bool isMouseButtonPressed;
extern bool isMouseButtonDown;
extern bool isMouseButtonReleased;

void draw();

#endif
