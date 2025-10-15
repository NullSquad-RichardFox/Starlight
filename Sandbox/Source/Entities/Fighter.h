#pragma once

#include "Starlight/Starlight.h"
#include "Ship.h"


class Fighter : public Ship
{
public:
	Fighter();

	virtual void OnUpdate(float deltaTime) override;

private:
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void Shoot();

	float MoveSpeed;
	float CurrentFireDelay;
	float FireDelay;
};