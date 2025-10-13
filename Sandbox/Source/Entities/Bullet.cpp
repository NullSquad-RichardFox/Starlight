#include "Bullet.h"
#include "Physics.h"
#include "Enemy.h"


Bullet::Bullet()
{
	Size = glm::vec2(10, 50);
	SlateTexture = std::make_shared<Texture>("Assets/Images/bullet.png");

	MoveSpeed = 1000.0f;
	BulletDamage = 5.f;

	PhysicsEngine::Get()->AddHitBox(this, std::bind(&Bullet::Collision, this, std::placeholders::_1));
}

Bullet::~Bullet()
{
	PhysicsEngine::Get()->RemoveHitBox(this);
}

void Bullet::OnUpdate(float deltaTime)
{
	Slate::OnUpdate(deltaTime);

	Position.y += MoveSpeed * deltaTime;
	if (Position.y > 1200)
	{
		RemoveFromParent();
	}
}

float Bullet::GetDamage() const
{
	return BulletDamage;
}

void Bullet::Collision(BoxSlate* other)
{
	if (EnemyShip* enemy = dynamic_cast<EnemyShip*>(other))
	{
		RemoveFromParent();
	}
}
