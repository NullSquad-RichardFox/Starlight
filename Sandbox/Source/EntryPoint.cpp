#include "Starlight/Starlight.h"
#include "Fighter.h"


int main()
{
	Application app;
	app.Initialize();

	Fighter f;

	auto l = std::make_shared<Layer>();
	l->GetRootSlate()
		->AddChild(f.GetSlate().get());
	
	app.AddLayer(l);
	app.Run();
	app.Shutdown();
}