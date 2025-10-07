#pragma once

#include "Starlight/Starlight.h"


class Bullet : public Slate
{
public:
	Bullet();

	virtual void OnUpdate(float deltaTime) override;

private:
	float MoveSpeed;
};