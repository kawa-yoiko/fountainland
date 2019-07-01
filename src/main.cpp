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

// 	b2Vec2 gravity;
// 	gravity.Set(0.0f, -10.0f);
// 	b2World* world = new b2World(gravity);
// 	b2CircleShape playerShape;
// 	playerShape.m_p.Set(700, 100);
// 	playerShape.m_radius = 0.2f;
// 	b2ParticleGroupDef playerDef;
// 	playerDef.flags = b2_elasticParticle;
// 	playerDef.groupFlags = b2_solidParticleGroup;
// 	playerDef.position.Set(700, 100);
// 	playerDef.shape = &playerShape;
// 	playerDef.color.Set(0, 255, 0, 255);
// 	const b2ParticleSystemDef pd;
// 	b2ParticleSystem* particleSystem = world->CreateParticleSystem(&pd);
// 	particleSystem->SetRadius(0.035f);
// 	auto playerGroup = particleSystem->CreateParticleGroup(playerDef);
// 	
// 	float32 hz = 60.0f;
// 	float32 timeStep = 1.0f / hz;
// 	int32 velocityIterations = 8;
// 	int32 positionIterations = 3;
// 	int32 particleIterations = b2CalculateParticleIterations(10, 0.04f, 1 / hz);
// 	while (true) {
// 		playerGroup->ApplyForce(gravity);
// 		world->Step(timeStep, velocityIterations, positionIterations, particleIterations);
// 		std::cout << world->GetParticleSystemList()->GetPositionBuffer()[0].x << "," << world->GetParticleSystemList()->GetPositionBuffer()[0].y << std::endl;
// 	}
}
