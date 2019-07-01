#include "Player.h"

Player::Player(float x,float y):GameObject(),playerGroup(nullptr){
	isPlayer = true;
	playerInitPos.x = x;
	playerInitPos.y = y;
}

Player::~Player(){
}

int Player::getParticleCount() const{
	return m_particleSystem->GetParticleCount();
}

b2Vec2* Player::getLinearVelocity() const{
	return m_particleSystem->GetVelocityBuffer();
}

void Player::applyLinearImpluse(const b2Vec2& impluse){
	playerGroup->ApplyLinearImpulse(impluse); 
}

const b2Vec2* Player::getPosition() const{
	return m_particleSystem->GetPositionBuffer();
}

void Player::addToWorld(){
	playerShape.m_p.Set(playerInitPos.x, playerInitPos.y);
	playerShape.m_radius = 1.0f;
	playerDef.flags = b2_elasticParticle;
	playerDef.groupFlags = b2_solidParticleGroup;
	playerDef.shape = &playerShape;
	playerDef.color.Set(0, 255, 0, 255);
	b2ParticleSystem* particleSystem = getParticleSystem();
	playerGroup = particleSystem->CreateParticleGroup(playerDef);
}

