#include "Enemy.h"
#include "Bullet.h"

#include "glm/gtc/random.hpp"


EnemyShip::EnemyShip()
{
    Position = glm::vec2(glm::linearRand(120, 1750), 960);
    Size = glm::vec2(150.f);
    SlateTexture = std::make_shared<Texture>("Assets/Images/enemy.png");

    CurrentFireDelay = 0;
    FireDelay = 1;

    SetShipTeam(ETeam::Enemy);
    SetShipMaxHealth(10.f);
    SetShipHealth(10.f);
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