#pragma once

#include "Starlight/Starlight.h"


class Fighter : public Slate
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
	float MoveSpeed;
	float CurrentFireDelay;
	float FireDelay;
};