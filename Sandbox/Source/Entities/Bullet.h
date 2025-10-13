#pragma once

#include "Starlight/Starlight.h"


class Bullet : public BoxSlate
{
public:
	Bullet();
	virtual ~Bullet() override;

	virtual void OnUpdate(float deltaTime) override;

	float GetDamage() const;

private:
	void Collision(BoxSlate* other);

	float MoveSpeed;
	float BulletDamage;
};