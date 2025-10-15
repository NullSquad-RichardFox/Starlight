#include "Bullet.h"
#include "Ship.h"
#include "Physics.h"


Bullet::Bullet()
{
	Size = glm::vec2(10, 50);
	SlateTexture = std::make_shared<Texture>("Assets/Images/bullet.png");

	MoveSpeed = 1000.0f;
	BulletDamage = 5.f;
	BulletDirection = glm::vec2(0, 1);

	PhysicsEngine::Get()->AddHitBox(this, std::bind(&Bullet::Collision, this, std::placeholders::_1));
}

Bullet::~Bullet()
{
	PhysicsEngine::Get()->RemoveHitBox(this);
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

Bullet* Bullet::SetDirection(glm::vec2 dir) 
{
	BulletDirection = glm::normalize(dir);
	return this;
}

Bullet* Bullet::SetTeam(ETeam team)
{
	BulletTeam = team;
	return this;
}

void Bullet::Collision(BoxSlate* other)
{
	if (Ship* ship = dynamic_cast<Ship*>(other))
	{
		if (ship->GetShipTeam() == BulletTeam) return;
	}
	else if (Bullet* bullet = dynamic_cast<Bullet*>(other))
	{
		if (bullet->BulletTeam == BulletTeam) return;
	}

	RemoveFromParent();
}
