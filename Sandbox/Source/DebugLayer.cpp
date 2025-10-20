#include "DebugLayer.h"


DebugLayer::DebugLayer()
{
    ChildCounterText = NewSlate<TextSlate>()->SetPosition(1700, 1040)->SetZOrder(999);
    FPSDisplayText = NewSlate<TextSlate>()->SetPosition(1800, 1000)->SetZOrder(999);

    GetRootSlate()->AddChild(ChildCounterText);
    GetRootSlate()->AddChild(FPSDisplayText);
}

void DebugLayer::OnUpdate(float deltaTime)
{
    ChildCounterText->SetText(std::format("Root Children: {}", GameLayerInst->GetRootSlate()->GetChildrenCount()));
    FPSDisplayText->SetText(std::format("FPS: {}", (uint32)(1.f / deltaTime)));
}

void SetControlledLayer(GameLayer* layer)
{
    GameLayerInst = layer;
}