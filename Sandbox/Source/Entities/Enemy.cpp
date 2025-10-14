#include "Enemy.h"
#include "Bullet.h"
#include "Physics.h"

#include "glm/gtc/random.hpp"


EnemyShip::EnemyShip()
{
    Position = glm::vec2(glm::linearRand(120, 1750), 960);
    Size = glm::vec2(150.f);
    SlateTexture = std::make_shared<Texture>("Assets/Images/enemy.png");

    ShipHealth = 20.f;
    CurrentFireDelay = 0;
    FireDelay = 1;

    PhysicsEngine::Get()->AddHitBox(this, std::bind(&EnemyShip::Collision, this, std::placeholders::_1));
}

EnemyShip::~EnemyShip()
{
    PhysicsEngine::Get()->RemoveHitBox(this);
}

void EnemyShip::OnUpdate(float deltaTime)
{
    BoxSlate::OnUpdate(deltaTime);

    CurrentFireDelay -= deltaTime;
    if (CurrentFireDelay <= 0)
    {
        CurrentFireDelay = FireDelay - CurrentFireDelay;
        AddChild(NewSlate<Bullet>()->SetDirection(glm::vec2(0, -1))->SetTeam(ETeam::Enemy)->SetPosition(Position + Size / 2.0f));
    }
}

void EnemyShip::Collision(BoxSlate* other)
{
    if (Bullet* bullet = dynamic_cast<Bullet*>(other))
    {
        if (bullet->GetTeam() == ETeam::Enemy) return;

        ShipHealth -= bullet->GetDamage();
        if (ShipHealth <= 0)
        {
            RemoveFromParent();
        }
    }
}
