#include "GameLayer.h"
#include "Fighter.h"


GameLayer::GameLayer()
{
    // Create fighter 
    GetRootSlate()->AddChild(NewSlate<Fighter>());
    
    // Start level
    
}

void GameLayer::OnUpdate(float deltaTime)
{
    Layer::OnUpdate(deltaTime);
}