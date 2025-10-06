#pragma once

#include "Starlight/Starlight.h"


class Slate;

class Fighter
{
public:
	Fighter();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void Shoot();

	const std::shared_ptr<Slate>& GetSlate() const { return FighterSlate; }

private:
	std::shared_ptr<Slate> FighterSlate;

	float MoveSpeed;
};