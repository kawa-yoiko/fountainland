#define _CRT_SECURE_NO_WARNINGS
#include "LevelLoader.h"

#include "raylib.h"

#include <cstdio>
#include <cstring>

World *loadLevel(const char *path)
{
    FILE *f = fopen(path, "r");
    if (!f) return nullptr;

    World *world = new World();

    int w;
    fscanf(f, "%d", &w);
    world->setWidth(w);

    char name[16];
    while (fscanf(f, "%15s", name) == 1) {
        if (strcmp(name, "ground") == 0) {
            int x, y;
            int x0, y0;
            bool first = true;
            std::vector<b2Vec2> p;
            Ground *ground = new Ground();
            while (fscanf(f, "%d%d", &x, &y) == 2) {
                p.push_back(b2Vec2(x, y));
                if (first) { x0 = x; y0 = y; first = false; }
            }
            p.push_back(b2Vec2(x0, y0));
            ground->setGroundBoundary(p);
            world->addGround(ground);
        } else if (strcmp(name, "bubble") == 0) {
            int x, y, sz, imp;
            fscanf(f, "%d%d%d%d", &x, &y, &sz, &imp);
            Bubble *bubble = new Bubble(Vector2 {(float)x, (float)y}, sz, imp);
            world->addBubble(bubble);
        } else if (strcmp(name, "cloud") == 0) {
            int x, y, w, h;
            float a;
            fscanf(f, "%d%d%d%d%f", &x, &y, &w, &h, &a);
            Cloud *cloud = new Cloud();
            cloud->setPosition(Vector2 {(float)x, (float)y});
            cloud->setSize(Vector2 {(float)w, (float)h});
            cloud->setAngle(a);
            world->addCloud(cloud);
        } else if (strcmp(name, "fountain") == 0) {
            // TODO: Cycle
            int x, y, vel;
            float a;
            fscanf(f, "%d%d%d%f", &x, &y, &vel, &a);
            Fountain *fountain = new Fountain();
            fountain->setPosition(Vector2 {(float)x, (float)y});
            fountain->setVelocity(vel);
            fountain->setDirection(a);
            world->addFountain(fountain);
        } else if (strcmp(name, "windmill") == 0) {
            int x, y, fansz;
            float a, w;
            fscanf(f, "%d%d%d%f%f", &x, &y, &fansz, &a, &w);
            Windmill *windmill = new Windmill();
            windmill->setPosition(Vector2 {(float)x, (float)y});
            windmill->setFanSize(fansz);
            windmill->setAngle(a);
			windmill->setVelocity(w);
            world->addWindmill(windmill);
		}else if (strcmp(name, "win") == 0) {
			int x1, y1, x2, y2;
			fscanf(f, "%d%d%d%d", &x1, &y1, &x2, &y2);
			world->addFinishLine(b2Vec2(x1, y1), b2Vec2(x2, y2));
		}
		else puts("> <");
    }

    fclose(f);
    return world;
}
