#include "GameLayer.h"
#include "Starlight/Starlight.h"
#include "Entities/Fighter.h"
#include "Physics.h"


int main()
{
	srand(time({}));

	Application app;
	
	app.Initialize();
	PhysicsEngine::Initialize();

	app.AddLayer(std::make_shared<GameLayer>());
	app.Run();
	
	PhysicsEngine::Shutdown();
	app.Shutdown();
}