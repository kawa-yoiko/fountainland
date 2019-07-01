#include "Player.h"

Player::Player(float x,float y):GameObject(),playerGroup(nullptr){
	isPlayer = true;
	playerInitPos.x = x;
	playerInitPos.y = y;
}

Player::~Player(){
	if(m_particleSystem)
		m_world->DestroyParticleSystem(m_particleSystem);
}

Vector2 Player::getLinearVelocity() const{
	return Vector2{ playerGroup->GetLinearVelocity().x,
		playerGroup->GetLinearVelocity().y };
}

void Player::applyLinearImpluse(const b2Vec2& impluse){
	playerGroup->ApplyLinearImpulse(impluse); 
}

const Vector2 Player::getPosition() const{
	return Vector2{ playerGroup->GetPosition().x,
		playerGroup->GetPosition().y };
}

void Player::addToWorld(){
	playerShape.m_p.Set(playerInitPos.x, playerInitPos.y);
	playerShape.m_radius = 0.2f;
	playerDef.flags = b2_elasticParticle;
	playerDef.groupFlags = b2_solidParticleGroup;
	playerDef.shape = &playerShape;
	playerDef.color.Set(0, 255, 0, 255);
	b2ParticleSystem* particleSystem = getParticleSystem();
	playerGroup = particleSystem->CreateParticleGroup(playerDef);
}

