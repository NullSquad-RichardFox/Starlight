#include "Ship.h"
#include "Physics.h"


Ship::Ship()
{
    ShipHealth = 10.f;

    PhysicsEngine::Get()->AddHitBox(this, std::bind(&Ship::Collide, this, std::placeholders::_1));
}

Ship::~Ship()
{
    PhysicsEngine::Get()->RemoveHitBox(this);
}

Ship* Ship::SetShipMaxHealth(float health)
{
    ShipMaxHealth = health;
    return this;
}

Ship* Ship::SetShipHealth(float health)
{
    ShipHealth = health;
    return this;
}

Ship* Ship::SetShipTeam(ETeam team)
{
    ShipTeam = team;
    return this;
}

void Ship::Collision(BoxSlate* other)
{

}