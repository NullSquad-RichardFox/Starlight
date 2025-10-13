#pragma once

#include "Starlight/Starlight.h"


class Fighter : public BoxSlate
{
public:
	Fighter();

	virtual void OnUpdate(float deltaTime) override;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void Shoot();

private:
	void Collide(BoxSlate* slate);

	TextSlate* ChildCounter;

	PhysicsEngineBinding HitBoxBinding;
	float MoveSpeed;
	float CurrentFireDelay;
	float FireDelay;
	float ShipHealth;
};