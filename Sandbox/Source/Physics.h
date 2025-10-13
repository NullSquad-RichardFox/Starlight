#pragma once

#include "Starlight/Starlight.h"


class BoxSlate;

struct PhysicsEngineBinding
{
public:
	PhysicsEngineBinding(BoxSlate* slate, void* func);
	~PhysicsEngineBinding();
}

class PhysicsEngine
{
public:
	PhysicsEngine();

	static void Initialize();
	static void Shutdown();

	static PhysicsEngine* Get() { return sEngineInstance; }
	
	void OnUpdate(float deltaTime);
	void AddHitBox(BoxSlate* slate, const std::function<void(BoxSlate*)>& callback);
	void RemoveHitBox(BoxSlate* slate);

private:
	inline static PhysicsEngine* sEngineInstance = nullptr;

	std::unordered_map<BoxSlate*, std::function<void(BoxSlate*)>> CollidableSlates;
};