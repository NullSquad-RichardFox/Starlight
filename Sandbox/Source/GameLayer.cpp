#include "GameLayer.h"
#include "Entities/Fighter.h"
#include "Entities/Enemy.h"
#include "Physics.h"


GameLayer::GameLayer()
{
    // Create fighter 
    ChildCounterText = NewSlate<TextSlate>()->SetPosition(1700, 1040)->SetZOrder(999);
    FPSDisplayText = NewSlate<TextSlate>()->SetPosition(1800, 1000)->SetZOrder(999);

    GetRootSlate()->AddChild(ChildCounterText);
    GetRootSlate()->AddChild(FPSDisplayText);
    GetRootSlate()->AddChild(NewSlate<Fighter>());
}

void GameLayer::OnUpdate(float deltaTime)
{
    Layer::OnUpdate(deltaTime);

    ChildCounterText->SetText(std::format("Root Children: {}", GetRootSlate()->GetChildrenCount()));
    FPSDisplayText->SetText(std::format("FPS: {}", (uint32)(1.f / deltaTime)));

    if (PhysicsEngine::Get()) PhysicsEngine::Get()->OnUpdate(deltaTime);

    CurrentSpawnDelay -= deltaTime;
    if (CurrentSpawnDelay <= 0)
    {
        GetRootSlate()->AddChild(NewSlate<EnemyShip>());
        CurrentSpawnDelay = SpawnDelay - CurrentSpawnDelay;
    }
}