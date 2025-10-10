#pragma once

#include "Starlight/Starlight.h"


class GameLayer : public Layer
{
public:
    GameLayer();

    virtual void OnUpdate(float deltaTime) override;

private:
};