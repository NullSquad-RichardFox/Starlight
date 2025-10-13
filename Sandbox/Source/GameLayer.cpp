#include "GameLayer.h"
#include "Entities/Fighter.h"
#include "Entities/Enemy.h"
#include "Physics.h"


GameLayer::GameLayer()
{
    // Create fighter 
    GetRootSlate()->AddChild(NewSlate<Fighter>());
}

void GameLayer::OnUpdate(float deltaTime)
{
    Layer::OnUpdate(deltaTime);

    if (PhysicsEngine::Get()) PhysicsEngine::Get()->OnUpdate(deltaTime);

    SpawnDelay -= deltaTime;
    if (SpawnDelay <= 0)
    {
        GetRootSlate()->AddChild(NewSlate<EnemyShip>());
        SpawnDelay = 1;
    }
}