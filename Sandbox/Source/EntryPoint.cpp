#include "Starlight/Starlight.h"
#include "GameLayer.h"
#include "DebugLayer.h"
#include "Entities/Fighter.h"
#include "Physics.h"


int main()
{
	srand(time({}));

	Application app;
	
	app.Initialize();
	PhysicsEngine::Initialize();

	auto gameLayer = std::make_shared<GameLayer>();
	app.AddLayer(gameLayer);
	auto debugLayer = std::make_shared<DebugLayer>();
	debugLayer->SetControlledLayer(gameLayer);
	app.AddLayer(debugLayer);

	app.Run();
	
	PhysicsEngine::Shutdown();
	app.Shutdown();
}