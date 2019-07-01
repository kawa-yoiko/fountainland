/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "Global.h"
#include "SceneStartup.h"

#include "raylib.h"
#include "Box2D/Box2D.h"

#include<iostream>
#include "World.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCR_W, SCR_H, "Fountain Land");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    preload();
    //--------------------------------------------------------------------------------------

    pushScene(new SceneStartup());
	
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;


// 	World world;
// 	Ground* ground = new Ground();
// 	std::vector<b2Vec2> bdy;
// 	bdy.push_back(b2Vec2(0.0f, 24.0f));
// 	bdy.push_back(b2Vec2(0.0f, 48.0f));
// 	bdy.push_back(b2Vec2(80.0f, 48.0f));
// 	bdy.push_back(b2Vec2(40.0f, 30.0f));
// 	ground->setGroundBoundary(bdy);
// 	world.addGround(ground);
// 	Player* player = new Player();
// 	player->setPosition(Vector2{ 10.0f, 10.0f });
// 	world.addPlayer(player);
// 
// 	
// 	
// 	float32 hz = 60.0f;
// 	float32 timeStep = 1.0f / hz;
// 	int32 velocityIterations = 8;
// 	int32 positionIterations = 3;
// 	int32 particleIterations = b2CalculateParticleIterations(10, 0.04f, 1 / hz);
// 	while (true) {
// 		world.m_world->Step(timeStep, velocityIterations, positionIterations, particleIterations);
// 		std::cout << world.m_world->GetParticleSystemList()->GetPositionBuffer()[0].x << "," << world.m_world->GetParticleSystemList()->GetPositionBuffer()[0].y << std::endl;
// 	}

}
