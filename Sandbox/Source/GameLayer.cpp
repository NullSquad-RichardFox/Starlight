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

    CurrentSpawnDelay -= deltaTime;
    if (CurrentSpawnDelay <= 0)
    {
        GetRootSlate()->AddChild(NewSlate<EnemyShip>());
        CurrentSpawnDelay = SpawnDelay - CurrentSpawnDelay;
    }
}