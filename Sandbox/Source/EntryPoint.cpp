#include "Starlight/Starlight.h"
#include "Fighter.h"


int main()
{
	Application app;
	app.Initialize();
	app.AddLayer(std::make_shared<Layer>());
	app.Run();
	app.Shutdown();
}