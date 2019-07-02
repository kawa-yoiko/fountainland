#pragma once
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Particle/b2ParticleGroup.h"
#include <vector>
#include "Windmill.h"
#include "Bubble.h"
#include "Cloud.h"
#include "Fountain.h"
#include "Player.h"
#include "Ground.h"

class World {
public:
	World();
	~World();
	b2World* m_world;
	b2ParticleSystem* m_particleSystem;

	void addWindmill(Windmill* windmill);
	void addBubble(Bubble* bubble);
	void addFountain(Fountain* fountain);
	void addCloud(Cloud* cloud);
	void addPlayer(Player* player);
	void addGround(Ground* ground);
	void addFinishLine(b2Vec2 finishStart, b2Vec2 finishEnd);
	void tick();
	bool checkWin();
	
	//Here stores all the interactable objects(fountains, bubbles, windmills, clouds)
	std::vector<Interactable*> interactableList;

    inline Player *getPlayer() const { return _player; }
    inline int getWidth() const { return _width; }
    inline void setWidth(int w) { _width = w < 80 ? 80 : w; }

protected:
    Player *_player;

    int _width;
	b2Vec2 *finishLine;
};
