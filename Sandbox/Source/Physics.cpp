#include "Physics.h"


PhysicsEngine::PhysicsEngine()
{

}

void PhysicsEngine::Initialize()
{
	ASSERT(sEngineInstance == nullptr, "Physics engine instance already created!");
	sEngineInstance = new PhysicsEngine();
}

void PhysicsEngine::Shutdown()
{
	delete sEngineInstance;
	sEngineInstance = nullptr;
}

void PhysicsEngine::OnUpdate(float deltaTime)
{
	for (const auto& [slate, callback] : CollidableSlates)
	{
		if (!slate)
		{
			CollidableSlates.erase(slate);
			continue;
		}

		for (const auto& [otherSlate, otherCallback] : CollidableSlates)
		{
			if (otherSlate == slate) continue;
			if (!otherSlate) continue;

			if (slate->GetPosition().x < otherSlate->GetPosition().x + otherSlate->GetSize().x && 
				slate->GetPosition().x + slate->GetSize().x > otherSlate->GetPosition().x && 
				slate->GetPosition().y < otherSlate->GetPosition().y + otherSlate->GetSize().y && 
				slate->GetPosition().y + slate->GetSize().y > otherSlate->GetPosition().y)
			{
				callback(otherSlate);
			}
		}
	}
}

void PhysicsEngine::AddHitBox(BoxSlate* slate, const std::function<void(BoxSlate*)>& callback)
{
	if (!slate) return;
	if (!callback) return;

	CollidableSlates[slate] = callback;
}

void PhysicsEngine::RemoveHitBox(BoxSlate* slate)
{
	if (!slate) return;

	if (auto it = CollidableSlates.find(slate); it != CollidableSlates.end())
		CollidableSlates.erase(it);
}

PhysicsEngineBinding::PhysicsEngineBinding(BoxSlate* slate, void* func)
{
	PhysicsEngine::Get()->AddHitBox(slate, std::bind(func, slate, std::placeholders::_1));
}

PhysicsEngineBinding::~PhysicsEngineBinding()
{
	PhysicsEngine::Get()->RemoveHitBox(slate);
}