#include "Player.h"

Player::Player(int x,int y):GameObject(){
	isPlayer = true;
	playerShape.m_p.Set(x, y);
	playerShape.m_radius = 0.2f;
	playerDef.flags = b2_elasticParticle;
	playerDef.groupFlags = b2_solidParticleGroup;
	playerDef.shape = &playerShape;
	playerDef.color.Set(0, 255, 0, 255);
}
