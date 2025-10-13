#pragma once

#include "Starlight/Starlight.h"


enum class ETeam
{
	Enemy, 
	Ally
}

class Bullet : public BoxSlate
{
public:
	Bullet();

	virtual void OnUpdate(float deltaTime) override;

	float GetDamage() const;
	ETeam GetTeam() const;

	void SetDirection(glm::vec2 dir);
	void SetTeam(ETeam team);

private:
	void Collision(BoxSlate* other);

	PhysicsEngineBinding HitBoxBinding;
	float MoveSpeed;
	float BulletDamage;
	glm::vec2 BulletDirection;
	ETeam BulletTeam;
};