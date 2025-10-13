#include "Enemy.h"
#include "Physics.h"
#include "Bullet.h"

#include "glm/gtc/random.hpp"


EnemyShip::EnemyShip()
{
    Position = glm::vec2(glm::linearRand(20, 1750), 960);
    Size = glm::vec2(150.f);
    SlateTexture = std::make_shared<Texture>("Assets/Images/enemy.png");

    ShipHealth = 20.f;

    PhysicsEngine::Get()->AddHitBox(this, std::bind(&EnemyShip::Collision, this, std::placeholders::_1));
}

EnemyShip::~EnemyShip()
{
    PhysicsEngine::Get()->RemoveHitBox(this);
}

void EnemyShip::OnUpdate(float deltaTime)
{
    BoxSlate::OnUpdate(deltaTime);
}

void EnemyShip::Collision(BoxSlate* other)
{
    if (Bullet* bullet = dynamic_cast<Bullet*>(other))
    {
        ShipHealth -= bullet->GetDamage();
        if (ShipHealth <= 0)
        {
            RemoveFromParent();
        }
    }
}
