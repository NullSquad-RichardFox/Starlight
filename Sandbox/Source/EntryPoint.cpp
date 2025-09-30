#include "iostream"
#include "Starlight/Core/Application.h"


int main()
{
	Application app;
	app.Initialize();
	app.Run();
	app.Shutdown();
}