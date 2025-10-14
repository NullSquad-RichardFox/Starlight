#pragma once

#include "Starlight/Starlight.h"


class EnemyShip : public BoxSlate
{
public:
    EnemyShip();
    virtual ~EnemyShip() override;

    virtual void OnUpdate(float deltaTime) override;
    
private:
    void Collision(BoxSlate* other);

    float ShipHealth;

    float CurrentFireDelay;
    float FireDelay;
};