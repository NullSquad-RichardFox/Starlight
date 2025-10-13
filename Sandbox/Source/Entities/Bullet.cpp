#include "Bullet.h"
#include "Physics.h"
#include "Enemy.h"


Bullet::Bullet()
{
	Size = glm::vec2(10, 50);
	SlateTexture = std::make_shared<Texture>("Assets/Images/bullet.png");

	MoveSpeed = 1000.0f;
	BulletDamage = 5.f;
	BulletDirection = glm::vec2(0, 1);

	HitBoxBinding = PhysicsEngineBinding(this, &Bullet::Collision);
}

void Bullet::OnUpdate(float deltaTime)
{
	Slate::OnUpdate(deltaTime);

	Position += BulletDirection * MoveSpeed * deltaTime;
	if (Position.x > 1920 || Position.y > 1080 || Position.x - Size.x < 0 || Position.y - Size.y < 0)
	{
		RemoveFromParent();
	}
}

float Bullet::GetDamage() const
{
	return BulletDamage;
}

ETeam Bullet::GetTeam() const
{
	return BulletTeam;
}

void Bullet::SetDirection(glm::vec2 dir) 
{
	BulletDirection = glm::normalize(dir);
}

void Bullet::SetTeam(ETeam team)
{
	BulletTeam = team;
}

void Bullet::Collision(BoxSlate* other)
{
	if (EnemyShip* enemy = dynamic_cast<EnemyShip*>(other))
	{
		RemoveFromParent();
	}
}
