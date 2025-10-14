#pragma once

#include "Starlight/Starlight.h"


enum class ETeam
{
	Enemy,
	Ally
};

class Bullet : public BoxSlate
{
public:
	Bullet();
	virtual ~Bullet() override;

	virtual void OnUpdate(float deltaTime) override;

	float GetDamage() const;
	ETeam GetTeam() const;

	Bullet* SetDirection(glm::vec2 dir);
	Bullet* SetTeam(ETeam team);

private:
	void Collision(BoxSlate* other);

	float MoveSpeed;
	float BulletDamage;
	glm::vec2 BulletDirection;
	ETeam BulletTeam;
};