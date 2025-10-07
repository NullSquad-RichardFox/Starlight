#include "Bullet.h"


Bullet::Bullet()
{
	Size = glm::vec2(10, 50);
	SlateTexture = std::make_shared<Texture>("Assets/Images/bullet.png");

	MoveSpeed = 1000.0f;
}

void Bullet::OnUpdate(float deltaTime)
{
	Slate::OnUpdate(deltaTime);

	Position.y += MoveSpeed * deltaTime;
	if (Position.y > 1200)
	{
		//RemoveFromParent();
	}
}
