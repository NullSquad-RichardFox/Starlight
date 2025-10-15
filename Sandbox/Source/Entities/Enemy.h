#pragma once

#include "Starlight/Starlight.h"
#include "Ship.h"


class EnemyShip : public Ship
{
public:
    EnemyShip();

    virtual void OnUpdate(float deltaTime) override;
    
private:
    float CurrentFireDelay;
    float FireDelay;
};