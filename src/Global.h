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

#ifdef __APPLE__
#define getMouseX() (GetMouseX() * 2)
#define getMouseY() (GetMouseY() * 2)
#else
#define getMouseX() (GetMouseX())
#define getMouseY() (GetMouseY())
#endif

Vector2 drawTextAnchored(
    const char *text, Vector2 pos, int sz, Color c,
    Vector2 anchor = Vector2{0.5, 0.5}, float spacing = 0);

extern bool isMouseButtonPressed;
extern bool isMouseButtonDown;
extern bool isMouseButtonReleased;

void draw();

#endif
