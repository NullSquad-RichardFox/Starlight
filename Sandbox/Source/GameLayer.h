#pragma once

#include "Starlight/Starlight.h"


class GameLayer : public Layer
{
public:
    GameLayer();

    virtual void OnUpdate(float deltaTime) override;

private:
    float SpawnDelay = 2.f;
    float CurrentSpawnDelay = 0;
};