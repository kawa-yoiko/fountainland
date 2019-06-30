#include "Player.h"

Player::Player(float x,float y):GameObject(),playerGroup(nullptr){
	isPlayer = true;
	playerShape.m_p.Set(x, y);
	playerShape.m_radius = 0.2f;
	playerDef.flags = b2_elasticParticle;
	playerDef.groupFlags = b2_solidParticleGroup;
	playerDef.shape = &playerShape;
	playerDef.color.Set(0, 255, 0, 255);
	b2ParticleSystem* particleSystem = getParticleSystem();
	playerGroup = particleSystem->CreateParticleGroup(playerDef);
}

Vector2 Player::getLinearVelocity() const{
	return Vector2{ playerGroup->GetLinearVelocity().x,
		playerGroup->GetLinearVelocity().y };
}

void Player::applyLinearImpluse(const b2Vec2& impluse){
	playerGroup->ApplyLinearImpulse(impluse); 
}

const Vector2& Player::getPosition() const{
	return Vector2{ playerGroup->GetPosition().x,
		playerGroup->GetPosition().y };
}

