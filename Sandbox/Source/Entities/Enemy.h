#pragma once

#include "Starlight/Starlight.h"


class EnemyShip : public BoxSlate
{
public:
    EnemyShip();

    virtual void OnUpdate(float deltaTime) override;
    
private:
    void Collision(BoxSlate* other);

    PhysicsEngineBinding HitBoxBinding;
    float ShipHealth;

    float CurrentFireDelay;
    float FireDelay;
};