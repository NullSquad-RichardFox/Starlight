#pragma once

#include "Starlight/Starlight.h"


class GameLayer : public Layer
{
public:
    GameLayer();

    virtual void OnUpdate(float deltaTime) override;

private:
    TextSlate* ChildCounterText;
    TextSlate* FPSDisplayText;

    float SpawnDelay = 2.f;
    float CurrentSpawnDelay = 0;
};