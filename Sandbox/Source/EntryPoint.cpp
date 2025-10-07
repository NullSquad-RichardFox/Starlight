#include "Starlight/Starlight.h"
#include "Fighter.h"


int main()
{
	Application app;
	app.Initialize();

	auto l = std::make_shared<Layer>();
	l->GetRootSlate()
		->AddChild(NewSlate<Fighter>());
	
	app.AddLayer(l);
	app.Run();
	app.Shutdown();
}