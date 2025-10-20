#pragma once

#include "Starlight/Starlight.h"


class GameLayer;

class DebugLayer : public Layer
{
public:
    DebugLayer();

    virtual void OnUpdate(float deltaTime) override;

    void SetControlledLayer(GameLayer* layer);

private:
    GameLayer* GameLayerInst;
    TextSlate* ChildCounterText;
    TextSlate* FPSDisplayText;
};