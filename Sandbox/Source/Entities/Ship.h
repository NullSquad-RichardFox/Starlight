#pragma once

#include "Starlight/Starlight.h"


enum class ETeam
{
	Enemy,
	Ally
};

class Ship : public BoxSlate
{
public:
    Ship();
    virtual ~Ship() override;

    float GetShipHealth() const { return ShipHealth; }
    float GetShipMaxHealth() const { return ShipMaxHealth; }
    ETeam GetShipTeam() const { return ShipTeam; }

    Ship* SetShipMaxHealth(float health);
    Ship* SetShipHealth(float health);
    Ship* SetShipTeam(ETeam team);

private:
    void Collide(BoxSlate* slate);

    float ShipHealth;
    float ShipMaxHealth;
    ETeam ShipTeam;
};